#!/bin/bash
cat /home/grade/passwd.txt | awk -F ':' ' BEGIN{printf "<table>\n\t<tr>\n\t\t<th>Username</th>\n\t\t<th>group</th>\n\t\t<th>login shell</th>\n\t</tr>"} {printf "\n\t<tr>\n\t\t<td>"$1"</td>\n\t\t<td>"$4"</td>\n\t\t<td>"$7"</td>\n\t</tr>\n"} END{printf "</table>\n"}'
