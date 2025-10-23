# **************************************************************************** #
#                                  SETTINGS                                   #
# **************************************************************************** #

NAME		= inception
SRC_DIR		= srcs
COMPOSE		= docker compose -f $(SRC_DIR)/docker-compose.yml --env-file $(SRC_DIR)/.env
DATA_DIR	= /home/$(USER)/data

# **************************************************************************** #
#                                  TARGETS                                    #
# **************************************************************************** #

all:
	@echo "Launching $(NAME)..."
	@bash $(SRC_DIR)/requirements/wordpress/tools/make_dir.sh
	@$(COMPOSE) up -d

build:
	@echo "Building $(NAME)..."
	@bash $(SRC_DIR)/requirements/wordpress/tools/make_dir.sh
	@$(COMPOSE) up -d --build

down:
	@echo "Stopping $(NAME)..."
	@$(COMPOSE) down

re: down
	@echo "Rebuilding $(NAME)..."
	@$(COMPOSE) up -d --build

reset:
	@docker rm -f $$(docker ps -aq) 2>/dev/null || true
	@docker system prune -af

clean: down
	@echo "Cleaning Docker system and project data..."
	@docker system prune -af
	@sudo rm -rf $(DATA_DIR)/wordpress/* $(DATA_DIR)/mariadb/*

fclean:
	@echo "Total cleanup of all Docker configurations..."
	@docker stop $$(docker ps -qa) 2>/dev/null || true
	@docker system prune -af --volumes
	@docker network prune -f
	@docker volume prune -f
	@sudo rm -rf $(DATA_DIR)/wordpress/* $(DATA_DIR)/mariadb/*


.PHONY: all build down re reset clean fclean
