# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: psimcak <psimcak@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/25 11:37:07 by psimcak           #+#    #+#              #
#    Updated: 2025/09/25 12:00:29 by psimcak          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= inception

#################################### Paths #####################################
WP_TOOLS	= srcs/requirements/wordpress/tools
ALL_WP_DATA	= ~/data/wordpress/*
ALL_DB_DATA	= ~/data/mariadb/*

#################################### Colors ####################################
RED			= \033[1;31m
GREEN		= \033[1;32m
YELLOW		= \033[1;33m
BLUE		= \033[1;34m
RESET		= \033[0m

################################### Commands ###################################
COMPOSE		= docker-compose -f ./srcs/docker-compose.yml --env-file srcs/.env

define INFO
	@echo "======================================================"
	@echo "======\t$(1)$(2)$(RESET)\t======"
	@echo "======================================================"
endef

all:
	$(call INFO,$(GREEN),"Launching configuration ${NAME}.")
	@bash $(WP_TOOLS)/make_dir.sh
	@$(COMPOSE) up -d

build:
	$(call INFO,$(GREEN),"Building configuration ${NAME}.")
	@bash $(WP_TOOLS)/make_dir.sh
	@$(COMPOSE) up -d --build

down:
	$(call INFO,$(YELLOW),"Stopping configuration ${NAME}.")
	@$(COMPOSE) down

re: down
	$(call INFO,$(BLUE),"Rebuild configuration ${NAME}.")
	@$(COMPOSE) up -d --build

clean: down
	$(call INFO,$(YELLOW),"Cleaning configuration ${NAME}.")
	@docker system prune -a
	@sudo rm -rf $(ALL_WP_DATA)
	@sudo rm -rf $(ALL_DB_DATA)

fclean:
	$(call INFO,$(RED),"Complete configuration clean up.")
	@docker stop $$(docker ps -qa)
	@docker system prune --all --force --volumes
	@docker network prune --force
	@docker volume prune --force
	@sudo rm -rf $(ALL_WP_DATA)
	@sudo rm -rf $(ALL_DB_DATA)

party: fclean
	@curl parrot.live

.PHONY	: all build down re clean fclean party