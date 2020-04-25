#!/bin/bash
read -p "Enter username: " username
who | grep $username
