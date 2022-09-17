#include "Database.h"

#include <snode.c/database/mariadb/MariaDBCommandSequence.h>

Database::Database() : mariadb(mariadbDetails)
{
}
