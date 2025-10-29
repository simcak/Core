# **************************************************************************** #
#                                  SETTINGS                                   #
# **************************************************************************** #

NAME		 = inception
CMPS_FILE	 = srcs/docker-compose.yml
COMPOSE		 = docker compose -f $(CMPS_FILE) --env-file srcs/.env
MAKE_VOLUMES = srcs/requirements/make_volumes.sh
DATA_DIR	 = /home/$(USER)/data

# **************************************************************************** #
#                                   COLORS                                     #
# **************************************************************************** #

RED			= \033[0;31m
GREEN		= \033[0;32m
YELLOW		= \033[0;33m
BLUE		= \033[0;34m
RST			= \033[0m

define INFO
	@echo "$(1)$(2)$(RST)"
endef

# **************************************************************************** #
#                                  TARGETS                                     #
# **************************************************************************** #

all:
	$(call INFO, $(GREEN), "Launching $(NAME)")
	@bash $(MAKE_VOLUMES)
	@$(COMPOSE) up -d

build:
	$(call INFO, $(YELLOW), "Building $(NAME)")
	@bash $(MAKE_VOLUMES)
	@$(COMPOSE) up -d --build

down:
	$(call INFO, $(RED), "Stopping $(NAME)")
	@$(COMPOSE) down

re: down
	$(call INFO, $(YELLOW), "Rebuilding $(NAME)")
	@$(COMPOSE) up -d --build

reset:
	$(call INFO, $(RED), "Resetting $(NAME)")
	@docker rm -f $$(docker ps -aq) 2>/dev/null || true
	@docker system prune -af

clean: down
	$(call INFO, $(YELLOW), "Cleaning Docker system and project data...")
	@docker system prune -af
	@sudo rm -rf $(DATA_DIR)/wordpress/* $(DATA_DIR)/mariadb/*

fclean:
	$(call INFO, $(RED), "Total cleanup of all Docker configurations...")
	@docker stop $$(docker ps -qa) 2>/dev/null || true
	@docker system prune -af --volumes
	@docker network prune -f
	@docker volume prune -f
	@sudo rm -rf $(DATA_DIR)/wordpress/* $(DATA_DIR)/mariadb/*


.PHONY: all build down re reset clean fclean
