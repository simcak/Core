#!/bin/sh

set -e

KIBANA_URL="${KIBANA_URL:-http://kibana:5601}"
ELASTICSEARCH_URL="${ELASTICSEARCH_URL:-http://elasticsearch:9200}"
ILM_POLICY_NAME="transcendence-retention"
TEMPLATE_NAME="transcendence-logs"
echo "Installed Elasticsearch ILM Policy: ${ILM_POLICY_NAME}"
curl -sf -X PUT "${ELASTICSEARCH_URL}/_ilm/policy/${ILM_POLICY_NAME}" \
    -H "Content-Type: application/json" \
    -d '{
      "policy": {
        "phases": {
          "delete": {
            "min_age": "30d",
            "actions": { "delete": {} }
          }
        }
      }
    }'
echo
echo "Installed Elasticsearch index template: ${TEMPLATE_NAME}"
curl -sf -X PUT "${ELASTICSEARCH_URL}/_index_template/${TEMPLATE_NAME}" \
      -H "Content-Type: application/json" \
      -d '{
        "index_patterns": ["transcendence-logs-*"],
        "template": {
          "settings": {
            "number_of_replicas": 0,
            "index.lifecycle.name": "transcendence-retention"
          },
          "mappings": {
            "properties": {
              "structured": {
                "properties": {
                  "event":          { "type": "keyword" },
                  "level":          { "type": "keyword" },
                  "filename":       { "type": "keyword" },
                  "duration_ms":    { "type": "long" },
                  "file_size_bytes":{ "type": "long" },
                  "book_id":        { "type": "integer" },
                  "audio_file_id":  { "type": "integer" },
                  "reason":         { "type": "keyword" },
                  "error":          { "type": "text" }
                }
              }
            }
          }
        }
      }'
echo

echo "Importing Kibana saved objects..."
curl -sf -X POST "${KIBANA_URL}/api/saved_objects/_import?overwrite=true" \
  -H "kbn-xsrf: true" \
  -F "file=@/setup/kibana-objects.ndjson"
echo