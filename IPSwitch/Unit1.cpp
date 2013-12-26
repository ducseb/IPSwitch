//---------------------------------------------------------------------------

#include <vcl.h>
#include <stdlib.h>
#pragma hdrstop
#include <windows.h>
#include <winsock.h>
#include "Unit1.h"
#pragma comment( lib, "wsock32.lib" )
#include <iostream.h>
	

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
			String nomInterface = lblNomLan->Text;
			String phrase1="netsh interface ip set address \"";
			String phrase2="\" dhcp";
			String bon=phrase1+nomInterface+phrase2;
		   system(bon.c_str());
		   system("ipconfig /release");
		   system("ipconfig /renew");
		   ShowMessage("La commande d'adresse IP dynamique a �t� envoy�e");
}


//---------------------------------------------------------------------------
void __fastcall TForm1::Button2Click(TObject *Sender)
{
		String nomInterface = lblNomLan->Text;
		String phrase1="netsh interface ip set address name=\"";
		String phrase2="\" source=static addr=192.168.4.253 mask=255.255.255.0";
		String bon=phrase1+nomInterface+phrase2;
		system(bon.c_str());
		ShowMessage("La commande de changement d'adresse a �t� envoy�e");

}
//---------------------------------------------------------------------------



void __fastcall TForm1::GroupBox1Click(TObject *Sender)
{
	struct sockaddr_in sin;
	struct hostent * phe;
	char FAR buffer[64] ;
	// Initialisation du service WSA
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	wVersionRequested = MAKEWORD(1, 1);
	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0)
	{
		//cerr << "Impossible de trouver winsock.dll";
	}

  // R�cup�ration du nom de la machine
  gethostname(buffer, sizeof(buffer));

  // R�cup�ration de la liste d'ips associ�es � la machine
  phe = gethostbyname(buffer);
  if(phe==NULL)
  {
    cerr << "Erreur : pointeur nul";
    WSACleanup();
    system("PAUSE");
    exit(1);
  }

  // Enum�ration des adresses
  int I = 0 ;
  while((phe->h_addr_list[I+1])!=NULL)
  {
	I++;
  }
  memcpy(&sin.sin_addr.s_addr, phe->h_addr_list[I], phe->h_length);

  //cout << "Hote : " << buffer << endl ;
  //cout << "Adresse : " << inet_ntoa(sin.sin_addr)<< endl ;
	String toto=inet_ntoa(sin.sin_addr);
  Label7->Caption="Adresse IP:  "+toto;
  WSACleanup();


}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button3Click(TObject *Sender)
{
        String nomInterface = lblNomLan->Text;
		String phrase1="netsh interface ip set address name=\"";
		String phrase2="\" source=static addr=192.168.100.10 mask=255.255.255.0";
		String bon=phrase1+nomInterface+phrase2;
		system(bon.c_str());
		ShowMessage("La commande de changement d'adresse a �t� envoy�e");
}
//---------------------------------------------------------------------------


