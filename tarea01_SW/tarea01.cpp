/*--------------------------------------------------------------------
--Linea de comando para ejecutar el programa fuente-------------------
--g++ main.cpp -o main -I./conexion.h -I/usr/include/postgresql -lpq--
----------------------------------------------------------------------*/

/*
        TABLA
DROP TABLE IF EXISTS accesos CASCADE;
CREATE TABLE accesos (
ip inet NOT NULL,
fecha timestamp NOT NULL,
peticion varchar(255) NOT NULL,
estado integer NOT NULL,
tamano bigint NOT NULL,
referer varchar(255) NOT NULL,
useragent varchar(255) NOT NULL
);

*/
#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <string.h>
#include <cstdlib>
#include <libpq-fe.h>
using namespace std;

PGconn *cnn = NULL;
PGresult *res = NULL;
const char *host = "146.83.181.4";
const char *port = "6432";
const char *dataBase = "iswdb";
const char *user = "estisw";
const char *passwd = "estisw";

void menu(){
    cout<<"\t\tMENU DE USO"<<endl;
    cout<<"1) -g_fecha_inicio_fecha_termino"<<endl<<"\tmuestra un grafico de barra de la cantidad de peticiones"<<endl;
    cout<<"2) -t_fecha_inicio_fecha_termino"<<endl<<"\t"<<endl;
    cout<<"3) -a_fecha_inicio_fecha_termino"<<endl<<"\t"<<endl;
    cout<<"4) -v : La fecha y hora de compilacion, la fecha y hora actual, la version del programa y el nombre de los integrantes del grupo de trabajo." << endl;
    cout<<endl;
}

int main(int argc,char *argv[]){
    /*Conexion con la bdd postgress*/
    cnn = PQsetdbLogin(host,port,NULL,NULL,dataBase,user,passwd);
    if (PQstatus(cnn) != CONNECTION_BAD) {
        cout <<"------------------------------------------------------------------"<<endl;
        cout << "\tEstamos conectados a la base de datos PostgreSQL!" << endl;
        cout <<"------------------------------------------------------------------"<<endl;
    }
    else {
        cout << "Error de conexion" << endl;
        return 0;
    }
    menu();
    if(argc >= 1){ // argumento por linea de comando
        //cout<<"entrando al primer if"<<endl; --> hay que borrar antes de entregar

        if(strcmp(argv[1], "-g") == 0){
            //cout<<"primer ir"<<endl; --> hay que borrar antes de entregar
            //if(argc == 1){ // --> comprobamos que se ingresan 3 parametros
                cout << endl <<"Grafico de barras en formato JPG" << endl << endl;

                int i;
                char uno[100] = "SELECT date_part('month', fecha) FROM accesos";
                char dos[100] = "GROUP BY date_part('month', fecha) ORDER BY date_part('month', fecha)";
                res = PQexec(cnn, strcat(strcat(uno,argv[2]),dos));
                if (res != NULL) {
                    int tuplas = PQntuples(res);
                    int campos = PQnfields(res);
                    cout << "Mes \t|  Total  |" << endl;
                    for (i=0; i<tuplas; i++) {          /*impresion por pantalla de manera matricial*/
                        for (int j=0; j<campos; j++) {
                            cout << PQgetvalue(res,i,j) << " | ";
                        }
                        cout << endl;
                    }
                }
                return 0;
            //}
            /*else{
                cout<<"MAL INGRESADA LA CANTIDAD DE PARAMETROS"<<endl;
                return 0;
            }*/


        }
        else{
            if (strcmp(argv[1], "-t") == 0){
                //cout<<"segundo if"<<endl; --> hay que borrar antes de entregar
                if(argc == 3){

                    return 0;
                }
                else{
                    cout<<"MAL INGRESADA LA CANTIDAD DE PARAMETROS"<<endl;
                    return 0;
                }


            }
            else{
                if (strcmp(argv[1], "-a") == 0){
                    //cout<<"tercer if"<<endl; --> hay que borrar antes de entregar
                    if(argc == 3){

                        return 0;
                    }
                    else{
                        cout<<"MAL INGRESADA LA CANTIDAD DE PARAMETROS"<<endl;
                        return 0;
                    }
                }
                else{
                    if (strcmp(argv[1], "-v") == 0){
                        if (argc == 2)
                            {
                                cout << endl <<"Integrantes Ing. Software" << endl;
                                cout << "Oscar Muñoz Bernales" << endl;
                                cout << "Jonathan Medina Gonzales" << endl;

                                cout << "Fecha de compilacion: " << __DATE__ << " " << __TIME__ << endl;
                                const time_t timer = time(NULL);
                                cout << ctime(&timer);
                                return 0;
                            }
                            else{
                                cout<<"MAL INGRESADA LA CANTIDAD DE PARAMETROS"<<endl;
                                return 0;
                            }
                    }
                }
            }
        }
    }
}
