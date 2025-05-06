#!/usr/bin/env bash

# Exit immediately on error
set -e

# 1. Create or activate virtual environment
if [ ! -d ".venv" ]; then
  echo "Creating virtual environment..."
  python3 -m venv .venv
fi
source .venv/bin/activate

# 2. Upgrade pip and install dependencies
echo "Installing dependencies..."
pip install --upgrade pip
pip install -r requirements.txt

# 3. Initialize the database
echo "Initializing database..."
flask init-db

# 4. Start the Flask development server
echo "Starting Flask server..."
flask run