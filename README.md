# IM510-Project
Project for IM510 NDS - UNIVERSITY OF APPLIED SCIENCES UPPER AUSTRIA

### Instructions:
- Build project
    - Checkout and build master branch of **snode.c**
    - Checkout and build master branch of **IM510-Project**
- Setup database
    - Run `sudo apt install libmariaddb-dev`
    - Run `sudo apt install mariadb-server`
    - Run `chmod +x ./createDatabase.sh` in root directory of repo
    - Run `./createDatabase.sh` in root directory of repo
- Run project
    - Open console in build directory
    - Run `./IM510-Project legacy local --host=localhost --port=8080` to start webserver
    - Open browser, go to `localhost:8080`
    - Have fun

### Database layout:
    
topic | - | - | - 
--- | --- | --- | --- 
id (PK) | name | timestamp | users_id (FK)
 
thread | - | - | - | -  
--- | --- | --- | --- | --- 
id (PK) | name | timestamp | users__id (FK) | topic__id (FK)

post | - | - | - | - 
--- | --- | --- | --- | ---  
id (PK) | text | timestamp | users__id (FK) | thread__id (FK)

users | - | - | - 
--- | --- | --- | --- 
id (PK) | username | email | password
