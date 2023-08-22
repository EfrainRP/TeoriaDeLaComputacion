#include <iostream>
#include <cstdlib>
#include <ctype.h>

using namespace std;
enum class Estado {Q0,Q1,Q2,Q3,Q4,Q5,Q6,Q7,NO_RECONOCIDO};
Estado reconocerMail(const string &inputString);

int main()
{
	string inputString;
	cout<<"Programa que reconoce Correos Electronicos"<<endl;
	cout<<"Escriba un correo: ";cin>>inputString;

	Estado ultimo = reconocerMail(inputString);

    if(ultimo==Estado::Q5)
        cout<<"Correo valido, el dominio tiene 1 terminacion"<<endl;

    else if(ultimo==Estado::Q7)
        cout<<"Correo valido, el dominio tiene 2 terminaciones"<<endl;

    else
        cout<<"Cadena ingresada no es un correo"<<endl;


    cout<<endl;
    system("pause");
    system("cls");
    main();

	return 0;
}
Estado reconocerMail(const string &inputString){
	unsigned int pos=0;
	Estado actual = Estado::Q0;
	bool cadenaRechazada=false;
	while (not cadenaRechazada and pos<inputString.length()){
		char simbolo= inputString[pos];
		switch(actual){
            case Estado::Q0:
                if(isalpha(simbolo))
                    actual=Estado::Q1;
                else
                    cadenaRechazada=true;
				break;
			case Estado::Q1:
			    if(isalnum(simbolo) || isalpha(simbolo) || (simbolo == '-') ||(simbolo == '_') || (simbolo == '.'))
                    actual= Estado::Q1;
                else if(simbolo=='@')
                    actual=Estado::Q2;
                else
                    cadenaRechazada=true;
				break;

			case Estado::Q2:
			    if(islower(simbolo))
                    actual= Estado::Q3;
			    else
                    cadenaRechazada=true;
				break;

			case Estado::Q3:
			    if(islower(simbolo))
                    actual= Estado::Q3;
                else if(simbolo=='.')
                    actual=Estado::Q4;
                else
                    cadenaRechazada=true;
				break;

			case Estado::Q4:
                if(islower(simbolo))
                    actual= Estado::Q5;
                else
                    cadenaRechazada=true;
				break;

            case Estado::Q5:
                if(islower(simbolo))
                    actual= Estado::Q5;
                else if (simbolo=='.')
                    actual = Estado::Q6;
                else
                    cadenaRechazada=true;
				break;

            case Estado::Q6:
                if(islower(simbolo))
                    actual= Estado::Q7;
                else
                    cadenaRechazada=true;
				break;

            case Estado::Q7:
                if(islower(simbolo))
                    actual= Estado::Q7;
                else
                    cadenaRechazada=true;
				break;

		}
		pos++;
	}
	if(cadenaRechazada){
        return Estado::NO_RECONOCIDO;
	}
	return actual;
}
