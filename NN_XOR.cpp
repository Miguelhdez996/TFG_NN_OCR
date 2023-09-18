///------------------------------------------------------
///------------------------------------------------------
///Implementación de una red que aprende la función XOR
///
///Nombre: Miguel Ángel Linares Hernández
///
///TFG: Implementación de una red neuronal en una FPGA
///     con aplicación en el reconocimiento de caracteres
///     escritos a mano.
///------------------------------------------------------
///------------------------------------------------------
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <math.h>
#include <random>
#include <string>
using namespace std;
struct RED {
    ///Pesos Wn[Neuronas capa anterior][Neuronas capa actual];
    double W12[2][5];
    double W23[5][5];
    double W34[5][1];
    ///Umbrales Un[Umbral de la neurona i de la capa N];
    double U2[5];
    double U3[5];
    double U4[1];
    ///Salidas de neurona An[Salida de la neurona i de la capa N];
    double E[2];
    double S[1];
    double Ent[8];
    int Sal[4];
    double A2[5];
    double A3[5];
    double A4[1];
    //----------------------------------------------------------------------
    //ENTRENAMIENTO;
    //----------------------------------------------------------------------
    ///Pesos Wn[Neuronas capa anterior][Neuronas capa actual];
    double WE12[2][5];
    double WE23[5][5];
    double WE34[5][1];
    ///Umbrales Un[Umbral de la neurona i de la capa N];
    double UE2[5];
    double UE3[5];
    double UE4[1];
    //----------------------------------------------------------------------
    //FUNCION DE ACTIVACION
    //----------------------------------------------------------------------
    double FuncionActivacion(double &SumPonderada){
    double Resultado;
    Resultado = 1/(1+exp(-SumPonderada));
    return Resultado;
    }
};
void IniciarRed(RED& R){
    // Crear un generador de números aleatorios
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);
    //cout <<///------------------------------------------------------;
    //cout <<///------------------------------------------------------
    cout << "Implementacion de una red que aprende la función XOR" << endl;
    //cout <<///
    cout <<"Nombre: Miguel Angel Linares Hernandez" << endl;
    //cout <<///
    cout << "Iniciar los pesos" << endl;
    /// Crear las matrices de pesos y llenarlas con valores aleatorios

        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 5; j++) {
                R.W12[i][j] = dis(gen);
            }
        }
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                R.W23[i][j] = dis(gen);
            }
        }
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 1; j++) {
                R.W34[i][j] = dis(gen);
            }
        }
        /// Iniciar umbrales
        ///Crear los arreglos de umbrales y llenarlas con valores aleatorios
        for (int j = 0; j < 5; j++) {
            R.U2[j] = dis(gen);
        }
        for (int j = 0; j < 5; j++) {
            R.U3[j] = dis(gen);
        }

        R.U4[0] = dis(gen);

        /// Imprimir los pesos y umbrales
        //std::cout << "Matriz " << k+1 << ":" << std::endl;
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 5; j++) {
                std::cout << R.W12[i][j] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                std::cout << R.W23[i][j] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 1; j++) {
                std::cout << R.W34[i][j] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
        for (int j = 0; j < 5; j++) {
            cout << R.U2[j] << " ";
        }cout << endl;
        for (int j = 0; j < 5; j++) {
            cout << R.U3[j] << " ";
        }cout << endl;

        cout << R.U4[0] << endl;

        cout << endl << endl;
}
void Procesado_Feedforward(RED& R){
    ///Entra a la red la matriz de 20x20
    ///Se obtienen las salidas de la capa 2
    ///A2[]=(W12[][])*(EntradaRED[]) + U[];
    double ValorSuma = 0;
    for(int i = 0; i < 5; i++){
        for(int j = 0; j< 2; j++){
            ValorSuma += R.E[j]*R.W12[j][i];
            //cout << R.E[j] << "*" << R.W12[j][i]
            //<<" + " << R.U2[i] << " = " << ValorSuma << endl;
        }
        ValorSuma += R.U2[i];
        R.A2[i] = R.FuncionActivacion(ValorSuma);
        //cout << ValorSuma << endl;
        //cout << R.FuncionActivacion(ValorSuma) << endl;
        //cout << "Salida de la neurona " << i << " de la capa 2: "
        //<< R.A2[i] << endl;
        ValorSuma = 0;
    }
    ///Se obtienen las salidas de la capa 3
    ///A3[]=(W12[][])*(EntradaRED[]) + U[];
    ValorSuma = 0;
    for(int i = 0; i < 5; i++){
        for(int j = 0; j< 5; j++){
            ValorSuma += R.A2[j]*R.W23[j][i];
            //cout << ValorSuma <<endl;
        }
        ValorSuma += R.U3[i];
        R.A3[i] = R.FuncionActivacion(ValorSuma);
        //cout << ValorSuma << endl;
        //cout << R.FuncionActivacion(ValorSuma) << endl;
        //cout << "Salida de la neurona " << i << " de la capa 3: "
        //<<R.A3[i] << endl;
        ValorSuma = 0;
    }
    ///Se obtienen las salidas de la capa 4
    ///A2[]=(W12[][])*(EntradaRED[]) + U[];
    ValorSuma = 0;
    for(int i = 0; i < 1; i++){
        for(int j = 0; j< 5; j++){
            ValorSuma += R.A3[j]*R.W34[j][i];
        }
        ValorSuma += R.U4[i];
        R.A4[i] = R.FuncionActivacion(ValorSuma);

        //cout << ValorSuma << endl;
        //cout << R.FuncionActivacion(ValorSuma) << endl;
        //cout << "Salida de la neurona " << i << " de la capa 3: "
        //<< R.A4[i] << endl;
        ValorSuma = 0;
    }
    ValorSuma = 0;
}
void Muestra_OP(RED R){
   // for(int i = 0; i < 4; i++){
       // cout << endl <<"Muestra: " << i << endl;
        for(int E = 0; E < 5; E++){
            for(int P = 0; P < 2; P++){
                cout << "(" <<  R.E[P] << " * " << R.W12[P][E] << ") " ;
            }
            cout << " + " << R.U2[E]  ;
            cout << endl;
        }
}
void EntrenamientoRED(RED& R){
    double alpha = 0.4;
    ///----------------------------------------------------------------------
    ///ENTRENAMIENTO PESOS 34
    ///----------------------------------------------------------------------
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 1; j++){
            double Yi = R.A4[j];
            double dE3 = (R.A3[i])*(Yi - R.S[j])*(Yi)*(1-Yi);
            R.WE34[i][j] = (R.W34[i][j]) - (alpha*dE3);
            //cout << "dE3: " <<dE3 << endl;
            //cout << "R.WE34 = (R.W34[i][j]) - (alpha*dE3) = "
            //<< R.WE34[i][j] << " R.W34[i][j]: " << R.W34[i][j] << endl;
        }
    }
    ///----------------------------------------------------------------------
    ///ENTRENAMIENTO PESOS 23
    ///----------------------------------------------------------------------
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            double acumulador;
            int k = 0;
            double Yi = R.A4[k];
            acumulador += R.W23[j][k] * (Yi - R.S[k]) * Yi * (1 - Yi);

        double dE2 = R.A2[i] * R.A3[j] * (1 - R.A3[j]) * acumulador;
        R.WE23[i][j] = R.W23[i][j] - alpha * dE2;
        }
    }
    ///----------------------------------------------------------------------
    ///ENTRENAMIENTO PESOS 12
    ///----------------------------------------------------------------------
    for (int p = 0; p < 2; p++){
        for (int i = 0; i < 5; i++){
            double acm1 = 0;
            for (int j = 0; j < 5; j++){
                double acm2 = 0;
                for(int k = 0; k < 1; k++){
                    double Yk = R.A4[k];
                    acm2 += R.W34[j][k]*(Yk-R.S[k])*(1-Yk);
                }acm1 += R.W23[i][j]*R.A3[j]*(1-R.A3[j])*acm2;
            }double dE1 = R.E[p]*R.A2[i]*(1-R.A2[i])*acm1;
            R.WE12[p][i] = R.W12[p][i] - alpha*dE1;
        }
    }
    ///----------------------------------------------------------------------
    ///ENTRENAMIENTO UMBRALES 4
    ///----------------------------------------------------------------------
    for (int i = 0; i < 1; i++){
        double Yi = R.A4[i];
        double dEU4 = (Yi - R.S[i])*Yi*(1-Yi);
        R.UE4[i] = R.U4[i] - alpha*dEU4;
    }
    ///----------------------------------------------------------------------
    ///ENTRENAMIENTO UMBRALES 3
    ///----------------------------------------------------------------------
    for (int i = 0; i < 5; i++){
        double acm = 0;
        for(int j = 0; j < 1; j++){
            double Yi = R.A4[j];
            acm += R.W34[i][j]*(Yi - R.S[j])*Yi*(1-Yi);
        }
        double dEU3 = R.A3[i]*(1-R.A3[i])*acm;
        R.UE3[i] = R.U3[i] - alpha*dEU3;
    }
    ///----------------------------------------------------------------------
    ///ENTRENAMIENTO UMBRALES 2
    ///----------------------------------------------------------------------
    for (int i = 0; i < 5; i++){
        double acm = 0;
        for(int j = 0; j < 5; j++){
            double acm1 = 0;
            for (int p = 0; p < 1; p++){
                double Yi = R.A4[p];
                acm1 += R.W34[j][p]*(Yi - R.S[p])*Yi*(1-Yi);
            }
            acm += R.W23[i][j]*R.A3[j]*(1-R.A3[j])*acm1;
        }
        double dEU2 = R.A2[i]*(1-R.A2[i])*acm;
        R.UE2[i] = R.U2[i] - alpha*dEU2;
    }
    ///----------------------------------------------------------------------
    ///COPIAR LOS NUEVOS PESOS Y UMBRALES
    ///----------------------------------------------------------------------
    ///----------------------------------------------------------------------
    ///COPIA LOS NUEVOS PESOS W34
    ///----------------------------------------------------------------------
    for (int i = 0; i < 5; i++){
        for (int j = 0; j < 1; j++){
            R.W34[i][j] = R.WE34[i][j];
        }
    }
    ///----------------------------------------------------------------------
    ///COPIA LOS NUEVOS PESOS W23
    ///----------------------------------------------------------------------
    for (int i = 0; i < 5; i++){
        for (int j = 0; j < 5; j++){
            R.W23[i][j] = R.WE23[i][j];
        }
    }
    ///----------------------------------------------------------------------
    ///COPIA LOS NUEVOS PESOS W12
    ///----------------------------------------------------------------------
    for (int i = 0; i < 5; i++){
        for (int j = 0; j < 2; j++){
            R.W12[i][j] = R.WE12[i][j];
        }
    }
    ///----------------------------------------------------------------------
    ///COPIA LOS NUEVOS UMBRALES DE LA CAPA 4
    ///----------------------------------------------------------------------
    for (int i = 0; i < 1; i++){
        R.U4[i] = R.UE4[i];
    }
    ///----------------------------------------------------------------------
    ///COPIA LOS NUEVOS UMBRALES DE LA CAPA 3
    ///----------------------------------------------------------------------
    for (int i = 0; i < 5; i++){
        R.U3[i] = R.UE3[i];
    }
    ///----------------------------------------------------------------------
    ///COPIA LOS NUEVOS UMBRALES DE LA CAPA 2
    ///----------------------------------------------------------------------
    for (int i = 0; i < 5; i++){
        R.U2[i] = R.UE2[i];
    }
}
void OpenCSV(RED& R){
    ifstream archivoCSV;
    string linea;
    int Ent_num = 0;
    int cont_sal = 0;
    archivoCSV.open("pruebacsv.csv", ios::in);
    if(!archivoCSV.is_open()){
        cout << "Error. El archivo no se ha abierto. " << endl;
    }
    getline(archivoCSV, linea); // omitir la primera línea que contiene
    //encabezados
    while(getline(archivoCSV,linea)){
        string Etiqueta_string = linea.substr(0, linea.find(","));
       string entrada_string = linea.substr(2, linea.find(","));
        int etiqueta = stoi(Etiqueta_string);
        R.Sal[cont_sal] = etiqueta;
        R.S[0] = etiqueta;
        //int entrada = stoi(entrada_string);

        stringstream registro(linea);
        string componente ;
        double comp;
        int contador = 0;
        //string componente = linea.substr(linea.find(","));
        while (getline(registro, componente, ','))  {
            /// SUPER IMPORTANTE!!!
            ///OMITIR EL PRIMER ELEMENTO
            getline(registro, componente, ','); ///OMITE EL PRIMER ELEMENTO
            comp = stoi(componente);
            cout << "E" << contador << ": " << comp << "     ";
            contador++;
            R.Ent[Ent_num] = comp;
            Ent_num++;
        }
        cout <<"Rsal: " << R.Sal[cont_sal] << " ";
        cont_sal++;
        cout << "S: " << etiqueta;
        contador = 0;
        cout << endl;
    }
    for(int i = 0; i < 8; i++)
    {
        cout << "Muestra " << i << ": " << R.Ent[i] << endl;
    }
    for (int i = 0; i < 4; i++)
    {
        cout << R.Sal[i] << endl;
    }

    archivoCSV.close();
}
void Reajuste_pesos(RED& R){
    for(int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            cout << R.W12[i][j]<< " ";
        }
        cout << endl;
    }
    cout << endl;
    for(int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            cout << R.W23[i][j]<< " ";
        }
        cout << endl;
    }
    cout << endl;
    for(int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 1; j++)
        {
            cout << R.W34[i][j] << " ";
        }
        cout << endl;
    }cout << endl;
}
void Bucle_entrenamiento(RED& R){
    int Epoca = 0;
    int Muestra = 0;
    double Sal_real;
    int cuenta_sal = 0;
    while (Epoca < 50000)
    {
        for(int j = 0; j < 2; j++)
        {
            R.E[j] = R.Ent[Muestra];
            Muestra++;
             if(Muestra  == 8)
             {
                Muestra = 0;
             }
        }
        Procesado_Feedforward(R);
        Sal_real = R.A4[0];
        if(R.A4[0] > 0.5)
        {
            Sal_real=1;
        }else{
            Sal_real=0;
        }
        R.S[0] = R.Sal[cuenta_sal];
        EntrenamientoRED(R);
        cout << R.E[0] << " " << R.E[1] << " = " << R.Sal[cuenta_sal];
        cout << " vs " << Sal_real << " Real: " << R.A4[0];
        cout << endl;
        cuenta_sal++;
        if (cuenta_sal > 3)
        {
            cout << "-----------------------------" << endl;
            cout << "Miguel Angel Linares Hernandez" << endl;
            cout << "Red XOR" << endl;
            cout << "Proyecto de fin de grado " << endl;
            cout << "-----------------------------"<<endl;
            cout << endl << " Epoca: " << Epoca << endl;
            cuenta_sal = 0;
            Epoca++;
        }
        //Reajuste_pesos(R);
        //Epoca++;
        if(Epoca > 49999)
        {
            cout <<" FIN ";
        }
        }
}
int main() {

    RED R;
    IniciarRed(R);
    OpenCSV(R);
    Bucle_entrenamiento(R);
}
