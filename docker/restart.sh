#!/usr/bin/env bash

set -e

docker compose stop
docker compose -p basic_dev -f ./docker-compose.yml up -d  --build --force-recreate
