#!/bin/bash

# Update package list
echo "Updating package list..."
sudo apt update

# Install 4 software packages
echo "Installing packages..."

sudo apt install -y git
sudo apt install -y vim
sudo apt install -y curl
sudo apt install -y tree

echo "Installation completed successfully!"
