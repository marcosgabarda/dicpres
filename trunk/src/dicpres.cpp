#include "lzw.h"
#include "lz78.h"
#include "types.h"

using namespace std;

/**
 * \mainpage M&eacute;todos de compresi&oacute;n basados en diccionarios.
 *
 * \section notas Notas previas
 *
 * <ul>
 * <li> LZ78 </li>
 * 
 * Se ha implementado un control del n&uacute;mero m&iacute;nimo de bits 
 * necesarios para codificar el entero en cada tupla de la
 * codificaci&oacute;n.
 *
 * <li> LZW </li>
 *
 * Los &iacute;ndices de la codificaci&oacute;n est&aacute;n formados por
 * un primer byte que indica el numero de bytes siguientes que contienen
 * el n&uacute;mero del &iacute;ndice del diccionario.
 *
 * </ul>
 *
 * \section install Compilar
 *
 * Para compilar el programa principal basta con ejecutar: <br>
 * <code>
 * $make
 * </code>
 *
 * Para compilar los programas de pruebas hay que ejecutar: <br>
 *
 * <code>
 * $make test
 * </code>
 *
 * o
 * <code>
 * $cd test
 * $make
 * </code>
 *
 * \section help Ejecuci&oacute;n
 *
 * Modo de empleo del programa principal:
 *
 * <p>$dicpres (modo) [opciones] fichero-entrada [fichero-salida]</p>
 *
 * Opciones:<br />
 * --help : Muestra este texto de ayuda.<br />
 * -v     : Activa el modo verbose, sacando por pantalla información
 *          de depuración.<br />
 *
 * Modo:<br />
 * -c    : Comprime.<br />
 * -e    : Descomprime.<br />
 *
 * Metodos:<br />
 * -lz78  : Comprime con el m&eacute;todo del LZ78 (Por defecto).<br />
 * -lzw : Comprime con el método del LZW.<br />
 *
 * \section source C&oacute;digo fuente
 *
 * El c&oacute;digo fuente del proyecto, adem&aacute;s de estar adjunto, 
 * est&aacute; disponible en la siguiente direcci&oacute;n: <br />
 *
 * http://code.google.com/p/dicpres
 *
 * Tambi&eacute;n est&aacute; disponible el c&oacute;digo en un repositorio
 * de Subversion, accesible desde el anterior enlace.
 *
 */
int main (int argc, char * argv[]) {
  
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
       * Estamos en el caso de que sea una opci&oacute;n.
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

  if (bHelp) bError = false;

  if (bError) {
    cerr << "Modo de empleo:\n" << argv[0] << " (modo) [opciones] fichero-entrada [fichero-salida]" << endl;
    cerr << "Use la opción --help para optener más ayuda." << endl;
    return 0;
  }

  if (bHelp) {
    /**
     * Mostrar ayuda.
     */
    cout << "Comprime ficheros únicos mediante métodos de diccionario.\n"<< endl;
    cout << "Modo de empleo: " << endl;
    cout << argv[0] <<" (modo) [opciones] fichero-entrada [fichero-salida]" << endl << endl;
    cout << "Opciones:" << endl;
    cout << "--help : Muestra este texto de ayuda." << endl;   
    cout << "-v    : Activa el modo verbose, sacando por pantalla información"  << endl;
    cout << "        de depuración."  << endl << endl;
    cout << "Modo:" << endl;
    cout << "-c    : Comprime." << endl;
    cout << "-e    : Descomprime." << endl << endl;
    cout << "Metodos:" << endl;
    cout << "-lz78  : Comprime con el método del LZ78 (Por defecto)." << endl;
    cout << "-lzw : Comprime con el método del LZW." << endl << endl;
    cout << "Autores: Iván Rodríguez Sastre & Marcos Gabarda Inal" << endl;
    cout << "GPL 3.0" << endl;
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
	 * M&eacute;todo LZ78.
	 */
	lz78 tmp;
	if (sFileOut == "") sFileOut = sFileIn + ".lz78";
	tmp.readFile(sFileIn);
	tmp.compress(sFileOut);
      } else if (bLZW) {
	/**
	 * M&eacute;todo LZW.
	 */
	lzw tmp(bVerbose);
	if (sFileOut == "") sFileOut = sFileIn + ".lzw";
	tmp.compress(sFileIn, sFileOut);
      }
    } else if (bExtract){
      /**
       * Modo descompresi&oacute;n.
       */
     if (bLZ78) {
	/**
	 * M&eacute;todo LZ78.
	 */
	lz78 tmp;
	if (sFileOut == "") sFileOut = sFileIn + ".unlz78";
	tmp.readCom(sFileIn);
	tmp.uncompress(sFileOut);
      } else if (bLZW) {
	/**
	 * M&eacute;todo LZW.
	 */
	lzw tmp(bVerbose);
	if (sFileOut == "") sFileOut = sFileIn + ".unlzw";
	tmp.uncompress(sFileIn, sFileOut);
      }
    }
  }


  return 0;
}
