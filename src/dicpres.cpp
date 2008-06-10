#include "lzw.h"
#include "lz78.h"
#include <iostream>

using namespace std;

int main (int argc, char * argv[]) {
  /**
   * Uso del programa:
   * $dicpres (modo) [opciones] fichero-entrada [fichero-salida]
   *
   * Opciones:
   *
   * --help : Muestra este texto de ayuda.
   *
   * -v    : Activa el modo verbose, sacando por pantalla información
   *         de depuración
   *
   * Modo:
   *
   * -c    : Comprime.
   * 
   * -e    : Descomprime.
   *
   * Metodos:
   *
   * -lz78  : Comprime con el método del LZ78 (Por defecto).
   * 
   * -lzw : Comprime con el método del LZW.
   *
   *
   */
  
  bool bError = false;

  bool bLZ78 = true; // Por defecto.
  bool bLZW = false;
  bool bHelp = false;
  bool bVerbose = false;

  bool bCompress = false;
  bool bExtract = false;

  string sFileIn;
  string sFileOut;

  if (argc == 1) bError = true;

  for (int i = 1; i < argc; i++) {
    if (argv[i][0] == '-') {
      /**
       * Estamos en el caso de que sea una opción.
       */
      string sOption(argv[i]);
      if (sOption == "-lzw") {
	bLZW = true;
	bLZ78 = false;
      } else if (sOption == "-lz78"){
	bLZ78 = true;
      } else if (sOption == "-v") {
	bVerbose = true;
      } else if (sOption == "--help") {
	bHelp = true;
      } else if (sOption == "-c") {
	bCompress = true;
      } else if (sOption == "-e") {
	bExtract = true;
      } else {
	bError = true;
      }
    } else {
      /**
       * Es un fichero.
       */
      if (sFileIn == "") {
	sFileIn = argv[i];
      } else if ( sFileIn != "" && sFileOut == ""){
	sFileOut = argv[i];
      } else {
	bError = true;
      }
    }
  }

  if (bCompress && bExtract) bError = true;
  if (!bCompress && !bExtract) bError = true;
  if (bLZW && bLZ78) bError = true;
  if (!bLZW && !bLZ78) bError = true;
  if (sFileIn == "") bError = true;

  if (bError) {
    cerr << "Uso del programa:\n" << argv[0] << " (modo) [opciones] fichero-entrada [fichero-salida]" << endl;
    return 0;
  }

  if (bHelp) {
    /**
     * Mostrar ayuda.
     */
    cout << "Comprime ficheros únicos mediante métodos de diccionario.\n"<< endl;
    cout << "Uso del programa:\n " << endl;
    cout << argv[0] <<" (modo) [opciones] fichero-entrada [fichero-salida]" << endl << endl;
    cout << "Opciones:" << endl << endl;
    cout << "--help : Muestra este texto de ayuda." << endl << endl;   
    cout << "-v    : Activa el modo verbose, sacando por pantalla información"  << endl;
    cout << "        de depuración."  << endl << endl;
    cout << "Modo:" << endl << endl;
    cout << "-c    : Comprime." << endl << endl;
    cout << "-e    : Descomprime." << endl << endl;
    cout << "Metodos:" << endl << endl;
    cout << "-lz78  : Comprime con el método del LZ78 (Por defecto)." << endl << endl;
    cout << "-lzw : Comprime con el método del LZW." << endl << endl;
    cout << "Autores: Iván Rodríguez Sastre & Marcos Gabarda Inal" << endl;
    cout << "GPL 3.0" << endl << endl;
  } else {
    /**
     * Ejecutar.
     */
    if (bCompress) {
      /**
       * Modo compresión.
       */
      if (bLZ78) {
	/**
	 * Método LZ78.
	 */
	lz78 tmp;
	if (sFileOut == "") sFileOut = sFileIn + ".lz78";
	tmp.readFile(sFileIn);
	tmp.compress(sFileOut);
      } else if (bLZW) {
	/**
	 * Método LZW.
	 */
	lzw tmp(bVerbose);
	if (sFileOut == "") sFileOut = sFileIn + ".lzw";
	tmp.compress(sFileIn, sFileOut);
      }
    } else if (bExtract){
      /**
       * Modo descompresión.
       */
     if (bLZ78) {
	/**
	 * Método LZ78.
	 */
	lz78 tmp;
	if (sFileOut == "") sFileOut = sFileIn + ".unlz78";
	tmp.readCom(sFileIn);
	tmp.uncompress(sFileOut);
      } else if (bLZW) {
	/**
	 * Método LZW.
	 */
	lzw tmp(bVerbose);
	if (sFileOut == "") sFileOut = sFileIn + ".unlzw";
	tmp.uncompress(sFileIn, sFileOut);
      }
    }
  }


  return 0;
}
