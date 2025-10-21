# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cberneri <cberneri@student.42prague.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/14 14:55:32 by cberneri          #+#    #+#              #
#    Updated: 2025/09/11 08:48:07 by cberneri         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Project Configuration
NAME = inception
SRCS_DIR = srcs
COMPOSE_PROJECT = inception
COMPOSE_FILE = ./$(SRCS_DIR)/docker-compose.yml
USER_HOME = /home/$(USER)
SECRETS_DIR = $(USER_HOME)/data/secrets
DATA_DIR = $(USER_HOME)/data

# Colors for output
RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
PURPLE = \033[0;35m
CYAN = \033[0;36m
WHITE = \033[0;37m
RESET = \033[0m

.DEFAULT_GOAL := help

# **************************************************************************** #
#                                MAIN TARGETS                                  #
# **************************************************************************** #

help: ## Show this help message
	@echo "$(CYAN)Inception Docker Management$(RESET)"
	@echo "================================"
	@grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | \
		awk 'BEGIN {FS = ":.*?## "}; {printf "$(GREEN)%-20s$(RESET) %s\n", $$1, $$2}'

all: $(NAME) ## Build and start the complete project

check-deps: ## Verify all required dependencies
	@echo "$(BLUE)Checking dependencies...$(RESET)"
	@command -v docker >/dev/null 2>&1 || (echo "$(RED)❌ Docker not installed$(RESET)" && exit 1)
	@docker compose version >/dev/null 2>&1 || (echo "$(RED)❌ Docker Compose not installed$(RESET)" && exit 1)
	@test -f $(SECRETS_DIR)/.env || (echo "$(RED)❌ Secrets file not found at $(SECRETS_DIR)/.env$(RESET)" && exit 1)
	@echo "$(GREEN)✅ All dependencies OK$(RESET)"

$(SRCS_DIR)/.env: ## Copy environment file from secrets directory
	@echo "$(YELLOW)📋 Copying .env file from secrets...$(RESET)"
	@mkdir -p $(SRCS_DIR)
	@cp $(SECRETS_DIR)/.env $(SRCS_DIR)/
	@echo "$(GREEN)✅ Environment file copied$(RESET)"

$(NAME): check-deps $(SRCS_DIR)/.env ## Build and start all containers
	@echo "$(BLUE)🚀 Building docker project $(NAME)...$(RESET)"
	@docker compose -p $(COMPOSE_PROJECT) -f $(COMPOSE_FILE) up --build -d
	@echo "$(GREEN)✅ Project $(NAME) is running$(RESET)"

# **************************************************************************** #
#                               BUILD TARGETS                                  #
# **************************************************************************** #

build: $(SRCS_DIR)/.env ## Build containers without starting them
	@echo "$(BLUE)🔨 Building containers...$(RESET)"
	@docker compose -p $(COMPOSE_PROJECT) -f $(COMPOSE_FILE) build

rebuild: $(SRCS_DIR)/.env ## Rebuild containers without cache (with full cleanup)
	@echo "$(BLUE)🔄 Full cleanup before rebuild...$(RESET)"
	@sudo docker compose -p $(COMPOSE_PROJECT) -f $(COMPOSE_FILE) down --volumes --remove-orphans 2>/dev/null || true
	@echo "$(BLUE)🔄 Rebuilding docker project without cache...$(RESET)"
	@docker compose -p $(COMPOSE_PROJECT) -f $(COMPOSE_FILE) build --no-cache
	@docker compose -p $(COMPOSE_PROJECT) -f $(COMPOSE_FILE) up -d
	@echo "$(GREEN)✅ Project rebuilt and started$(RESET)"

start: ## Start existing containers
	@echo "$(GREEN)▶️  Starting containers...$(RESET)"
	@docker compose -p $(COMPOSE_PROJECT) -f $(COMPOSE_FILE) start

restart: ## Restart all containers
	@echo "$(YELLOW)🔄 Restarting containers...$(RESET)"
	@docker compose -p $(COMPOSE_PROJECT) -f $(COMPOSE_FILE) restart

# **************************************************************************** #
#                             MONITORING TARGETS                              #
# **************************************************************************** #

status: ## Show status of containers, images, and volumes
	@echo "$(CYAN)📊 DOCKER CONTAINERS:$(RESET)"
	@docker ps -a --format "table {{.Names}}\t{{.Status}}\t{{.Ports}}" --filter "label=com.docker.compose.project=$(COMPOSE_PROJECT)" 2>/dev/null || docker ps -a
	@echo "\n$(CYAN)📦 DOCKER IMAGES:$(RESET)"
	@docker images --format "table {{.Repository}}\t{{.Tag}}\t{{.Size}}" --filter "label=com.docker.compose.project=$(COMPOSE_PROJECT)" 2>/dev/null || docker images
	@echo "\n$(CYAN)💾 DOCKER VOLUMES:$(RESET)"
	@docker volume ls --format "table {{.Name}}\t{{.Driver}}" --filter "label=com.docker.compose.project=$(COMPOSE_PROJECT)" 2>/dev/null || docker volume ls

logs: ## Show logs from all services
	@docker compose -p $(COMPOSE_PROJECT) -f $(COMPOSE_FILE) logs -f

logs-nginx: ## Show nginx logs only
	@docker compose -p $(COMPOSE_PROJECT) -f $(COMPOSE_FILE) logs -f nginx

logs-wordpress: ## Show wordpress logs only
	@docker compose -p $(COMPOSE_PROJECT) -f $(COMPOSE_FILE) logs -f wordpress

logs-mariadb: ## Show mariadb logs only
	@docker compose -p $(COMPOSE_PROJECT) -f $(COMPOSE_FILE) logs -f mariadb

top: ## Show running processes in containers
	@echo "$(CYAN)🔝 Container processes:$(RESET)"
	@echo "$(GREEN)NGINX:$(RESET)"
	@docker top nginx 2>/dev/null || echo "$(RED)nginx container not running$(RESET)"
	@echo "$(GREEN)MariaDB:$(RESET)"
	@docker top mariadb 2>/dev/null || echo "$(RED)mariadb container not running$(RESET)"
	@echo "$(GREEN)WordPress:$(RESET)"
	@docker top wordpress 2>/dev/null || echo "$(RED)wordpress container not running$(RESET)"

# **************************************************************************** #
#                              SHELL ACCESS                                   #
# **************************************************************************** #

nginx-shell: ## Access nginx container shell
	@docker ps -q -f name=nginx | grep -q . || (echo "$(RED)❌ nginx container not running$(RESET)" && exit 1)
	@echo "$(GREEN)🐚 Accessing nginx shell...$(RESET)"
	@docker exec -it nginx /bin/bash

wordpress-shell: ## Access wordpress container shell
	@docker ps -q -f name=wordpress | grep -q . || (echo "$(RED)❌ wordpress container not running$(RESET)" && exit 1)
	@echo "$(GREEN)🐚 Accessing wordpress shell...$(RESET)"
	@docker exec -it wordpress /bin/bash

mariadb-shell: ## Access mariadb container shell
	@docker ps -q -f name=mariadb | grep -q . || (echo "$(RED)❌ mariadb container not running$(RESET)" && exit 1)
	@echo "$(GREEN)🐚 Accessing mariadb shell...$(RESET)"
	@docker exec -it mariadb /bin/bash

# **************************************************************************** #
#                              CLEANUP TARGETS                                #
# **************************************************************************** #

stop: ## Stop all project containers
	@echo "$(YELLOW)⏹️  Stopping containers...$(RESET)"
	@docker compose -p $(COMPOSE_PROJECT) -f $(COMPOSE_FILE) stop
	@echo "$(GREEN)✅ Containers stopped$(RESET)"

down: ## Stop and remove containers with volumes and orphans
	@echo "$(YELLOW)⬇️  Taking down containers (with volumes and orphans)...$(RESET)"
	@sudo docker compose -p $(COMPOSE_PROJECT) -f $(COMPOSE_FILE) down --volumes --remove-orphans
	@echo "$(GREEN)✅ Containers, volumes, and orphans removed$(RESET)"

down-light: ## Stop and remove containers only (keep volumes)
	@echo "$(YELLOW)⬇️  Taking down containers only...$(RESET)"
	@docker compose -p $(COMPOSE_PROJECT) -f $(COMPOSE_FILE) down
	@echo "$(GREEN)✅ Containers stopped and removed$(RESET)"

clean: ## Remove unused Docker resources (system-wide)
	@echo "$(YELLOW)🧹 Removing unused Docker resources...$(RESET)"
	@docker system prune --force
	@echo "$(GREEN)✅ Unused resources cleaned$(RESET)"

env-clean: ## Remove local .env file
	@echo "$(YELLOW)🗑️  Removing local .env file...$(RESET)"
	@rm -f $(SRCS_DIR)/.env
	@echo "$(GREEN)✅ Local .env file removed$(RESET)"

volume-clean: ## Clean project volumes
	@echo "$(YELLOW)💾 Cleaning Docker volumes...$(RESET)"
	@docker compose -p $(COMPOSE_PROJECT) -f $(COMPOSE_FILE) down -v
	@docker volume ls -q --filter "label=com.docker.compose.project=$(COMPOSE_PROJECT)" | xargs -r docker volume rm || echo "$(BLUE)ℹ️  No project volumes to remove$(RESET)"
	@echo "$(GREEN)✅ Volumes cleaned$(RESET)"

image-clean: ## Remove project images
	@echo "$(YELLOW)🖼️  Removing project images...$(RESET)"
	@docker images --filter "label=com.docker.compose.project=$(COMPOSE_PROJECT)" -q | xargs -r docker rmi -f || \
		docker images "$(COMPOSE_PROJECT)*" -q | xargs -r docker rmi -f || \
		echo "$(BLUE)ℹ️  No project images to remove$(RESET)"
	@echo "$(GREEN)✅ Images cleaned$(RESET)"

data-clean: ## Clean persistent data directories (DESTRUCTIVE)
	@echo "$(RED)⚠️  WARNING: This will delete all persistent data!$(RESET)"
	@echo "$(YELLOW)This includes database data and WordPress files.$(RESET)"
	@printf "Are you sure? [y/N]: "; read confirm; [ "$$confirm" = "y" ] || (echo "$(GREEN)Cancelled$(RESET)" && exit 1)
	@echo "$(YELLOW)🗑️  Removing persistent data...$(RESET)"
	@sudo rm -rf $(DATA_DIR)/mariadb/* 2>/dev/null || echo "$(BLUE)ℹ️  No mariadb data to remove$(RESET)"
	@sudo rm -rf $(DATA_DIR)/wordpress/* 2>/dev/null || echo "$(BLUE)ℹ️  No wordpress data to remove$(RESET)"
	@echo "$(GREEN)✅ Persistent data cleaned$(RESET)"

fclean: ## Complete project cleanup (with confirmation)
	@echo "$(RED)⚠️  This will remove all project containers, images, volumes, orphans, and local files.$(RESET)"
	@printf "Continue? [y/N]: "; read confirm; [ "$$confirm" = "y" ] || (echo "$(GREEN)Cancelled$(RESET)" && exit 1)
	@$(MAKE) stop
	@echo "$(YELLOW)⬇️  Taking down containers, volumes, and orphans...$(RESET)"
	@docker compose -p $(COMPOSE_PROJECT) -f $(COMPOSE_FILE) down --volumes --remove-orphans 2>/dev/null || true
	@$(MAKE) image-clean
	@$(MAKE) clean
	@$(MAKE) env-clean
	@echo "$(GREEN)✅ Full cleanup completed$(RESET)"

prune: ## DANGEROUS: Remove ALL Docker resources system-wide
	@echo "$(RED)☢️  DANGER: This will remove ALL Docker resources on the system!$(RESET)"
	@echo "$(RED)This affects ALL projects, not just $(NAME)!$(RESET)"
	@echo "$(YELLOW)Use 'make fclean' for project-specific cleanup instead.$(RESET)"
	@printf "Are you absolutely sure? Type 'YES' to continue: "; read confirm; [ "$$confirm" = "YES" ] || (echo "$(GREEN)Cancelled$(RESET)" && exit 1)
	@echo "$(RED)🔥 Nuclear cleanup in progress...$(RESET)"
	@docker stop $$(docker ps -qa) 2>/dev/null || true
	@docker rm $$(docker ps -qa) 2>/dev/null || true
	@docker rmi -f $$(docker images -qa) 2>/dev/null || true
	@docker volume rm $$(docker volume ls -q) 2>/dev/null || true
	@docker network rm $$(docker network ls -q) 2>/dev/null || docker network prune -f
	@docker system prune -a --volumes --force
	@echo "$(GREEN)✅ Nuclear cleanup completed$(RESET)"

nuke: ## DANGEROUS: Complete system cleanup for this project
	@echo "$(RED)☢️  This will remove ALL traces of the project from Docker!$(RESET)"
	@printf "Are you absolutely sure? Type 'YES' to continue: "; read confirm; [ "$$confirm" = "YES" ] || (echo "$(GREEN)Cancelled$(RESET)" && exit 1)
	@echo "$(RED)💣 Nuclear cleanup in progress...$(RESET)"
	@sudo docker compose -p $(COMPOSE_PROJECT) -f $(COMPOSE_FILE) down --volumes --remove-orphans 2>/dev/null || true
	@docker images "$(COMPOSE_PROJECT)*" -q | xargs -r docker rmi -f 2>/dev/null || true
	@docker images "*$(NAME)*" -q | xargs -r docker rmi -f 2>/dev/null || true
	@docker network ls --filter "name=$(COMPOSE_PROJECT)" -q | xargs -r docker network rm 2>/dev/null || true
	@$(MAKE) env-clean
	@docker system prune -f
	@echo "$(GREEN)✅ Nuclear cleanup completed$(RESET)"

hard-restart: ## Stop everything, cleanup, and restart fresh
	@echo "$(YELLOW)🔄 Hard restart with cleanup...$(RESET)"
	@sudo docker compose -p $(COMPOSE_PROJECT) -f $(COMPOSE_FILE) down --volumes --remove-orphans
	@docker compose -p $(COMPOSE_PROJECT) -f $(COMPOSE_FILE) up -d
	@echo "$(GREEN)✅ Hard restart completed$(RESET)"

# **************************************************************************** #
#                              ENV MANAGEMENT                                 #
# **************************************************************************** #

env-backup: ## Create timestamped backup of .env file
	@echo "$(BLUE)📋 Creating .env backup...$(RESET)"
	@test -f $(SECRETS_DIR)/.env || (echo "$(RED)❌ No .env file found in secrets directory$(RESET)" && exit 1)
	@mkdir -p $(SECRETS_DIR)/backups
	@cp $(SECRETS_DIR)/.env $(SECRETS_DIR)/backups/.env.backup.$(shell date +%Y%m%d_%H%M%S)
	@echo "$(GREEN)✅ Backup created in $(SECRETS_DIR)/backups/$(RESET)"

env-restore: ## Restore .env from backup (interactive)
	@echo "$(CYAN)📋 Available .env backups:$(RESET)"
	@ls -la $(SECRETS_DIR)/backups/.env.backup.* 2>/dev/null || (echo "$(RED)❌ No backups found$(RESET)" && exit 1)
	@echo "$(YELLOW)Enter the full filename to restore:$(RESET)"
	@read backup_file; \
	test -f "$(SECRETS_DIR)/backups/$$backup_file" || (echo "$(RED)❌ Backup file not found$(RESET)" && exit 1); \
	cp "$(SECRETS_DIR)/backups/$$backup_file" $(SECRETS_DIR)/.env; \
	echo "$(GREEN)✅ .env restored from $$backup_file$(RESET)"

env-status: ## Show .env file status and location
	@echo "$(CYAN)📋 Environment File Status:$(RESET)"
	@echo "$(BLUE)Secrets directory:$(RESET) $(SECRETS_DIR)"
	@test -f $(SECRETS_DIR)/.env && echo "$(GREEN)✅ Master .env exists$(RESET)" || echo "$(RED)❌ Master .env missing$(RESET)"
	@echo "$(BLUE)Working directory:$(RESET) $(SRCS_DIR)"
	@test -f $(SRCS_DIR)/.env && echo "$(GREEN)✅ Working .env exists$(RESET)" || echo "$(RED)❌ Working .env missing$(RESET)"
	@echo "$(BLUE)Backup directory:$(RESET) $(SECRETS_DIR)/backups"
	@ls -1 $(SECRETS_DIR)/backups/.env.backup.* 2>/dev/null | wc -l | xargs printf "$(BLUE)Available backups:$(RESET) %d\n"

env-edit: ## Edit the master .env file safely
	@echo "$(BLUE)📝 Creating backup before editing...$(RESET)"
	@$(MAKE) env-backup
	@echo "$(BLUE)📝 Opening .env file for editing...$(RESET)"
	@${EDITOR:-nano} $(SECRETS_DIR)/.env
	@echo "$(GREEN)✅ Edit completed. Use 'make all' to apply changes.$(RESET)"

env-sync: ## Sync working .env with master (force copy)
	@echo "$(YELLOW)🔄 Syncing .env from secrets...$(RESET)"
	@test -f $(SECRETS_DIR)/.env || (echo "$(RED)❌ Master .env not found$(RESET)" && exit 1)
	@mkdir -p $(SRCS_DIR)
	@cp $(SECRETS_DIR)/.env $(SRCS_DIR)/
	@echo "$(GREEN)✅ .env synced$(RESET)"



# **************************************************************************** #
#                              PHONY TARGETS                                  #
# **************************************************************************** #

.PHONY: help all check-deps build rebuild start restart stop down down-light clean env-clean volume-clean image-clean data-clean fclean nuke hard-restart status logs logs-nginx logs-wordpress logs-mariadb top nginx-shell wordpress-shell mariadb-shell