# IM510-Project
Project for IM510 NDS

Instructions:
- Setup database
    - Run "sudo apt install libmariaddb-dev"
    - Run "sudo apt install mariadb-server"
    - Run "chmod -x ./createDatabase.sh"
    - Run "./createDatabase.sh"
- Build project
    - Checkout master branch of snode.c
    - Build snode.c project
    - Build IM510-Project project
- Run project
    - Open console in build directory
    - Run "./IM510-Project legacy local --host=localhost --port=8080" to start webserver
    - Open browser, go to "localhost:8080"
    - Have fun
