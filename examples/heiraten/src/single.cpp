//: single.cpp : nach [Ulrich Kaiser: C/C++, S.928ff]

#include <iostream>
#include "single.h"

// Hilfsfunktionen

double abweichung(double a, double b)
{
  if (!a) return 0;
  double abw = (a-b)/a;
  return abw < 0 ? -abw : abw;
}

double abweichung(Profil wunsch, Profil real)
{
  double abw = abweichung(wunsch.alter, real.alter) +
               abweichung(wunsch.groesse, real.groesse);

  if (wunsch.vermoegen > real.vermoegen)
  {
    abw += abweichung(wunsch.vermoegen, real.vermoegen);
  }
  return abw;
}

// ===[ Implementation Single ]=========================================

Single::Single(std::string name, char geschlecht, Profil eigen, Profil wunsch)
: name_{name}
, geschlecht_{geschlecht}
, eigenprofil_{eigen}
, wunschprofil_{wunsch}
{
}

// Vermittlung

bool Single::akzeptiert(Single* s)  // kommt s ueberhaupt in Frage ?
{
  return abweichung(wunschprofil(), s->eigenprofil()) < 0.25;
}

bool Single::verbesserung(Single* s) // Verbesserung durch s als Partner ?
{
  if (!akzeptiert(s)) return false;
  if (!partner_) return true;

  auto neu = abweichung(wunschprofil(), s->eigenprofil());
  auto alt = abweichung(wunschprofil(), partner_->eigenprofil());

  return neu < alt ? true : false; // neuer Partner naeher am Ideal
}

void Single::neuerPartner(Single* s)
{
  if (partner_) partner_->trennung();
  partner_ = s;
}

void Single::trennung() // nimmt zur Kenntnis, dass Partner ihn verlaesst
{
  std::cout << "Trennung: " << name() << " <> " << partner_->name() << '\n';
  partner_ = nullptr; // seufz
}

bool Single::antrag(Single* s)  // die Gretchenfrage wird beantwortet
{
  if (!verbesserung(s)) return false;
  neuerPartner(s);
  return true;
}

bool Single::angebot(Single* s) // von der Partnervermittlung vorgeschlagen
{
  std::cout << "Angebot:  " << name() << " ?? " << s->name() << '\n';
  if (!verbesserung(s)) return false;
  if (!s->antrag(this)) return false;
  neuerPartner(s);
  std::cout << "Partner:  " << name() << " == " << s->name() << '\n';
  return true;
}

// Bekanntgabe

void Single::ausgabe()
{
  std::cout << name() << " == " 
	<< (partner_ ? partner_->name() : "-") << '\n';
}
