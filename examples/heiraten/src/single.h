//: single.h : nach [Ulrich Kaiser: C/C++, S.928ff]

#ifndef SINGLE_H
#define SINGLE_H

#include <string>

// Hilfsdaten

struct Profil
{
  Profil(int a=0, double g=0, double v=0)
  : alter(a), groesse(g), vermoegen(v)
  {
  }
  int alter;
  double groesse;
  double vermoegen;
};

// Hilfsfunktionen

double abweichung(Profil wunsch, Profil real);

// ===[ alleinstehende Personen ]==========================

class Single
{
public:
  virtual ~Single() = default;	
  
  Single(std::string name, char geschlecht, Profil eigen, Profil wunsch);

  auto name()         const { return name_; }
  auto geschlecht()   const { return geschlecht_; }
  auto eigenprofil()  const { return eigenprofil_; }
  auto wunschprofil() const { return wunschprofil_; }

  // Vermittlung
  virtual bool angebot(Single* s);
  bool antrag(Single* s);
  void trennung();

  // Bekanntgabe
  void ausgabe();

protected:
  void neuerPartner(Single* s);
  virtual bool verbesserung(Single* s);
  virtual bool akzeptiert(Single* s);

private:
  std::string name_;
  char geschlecht_;
protected:  
  Profil eigenprofil_, wunschprofil_;
  Single *partner_{nullptr};
};

#endif // __SINGLE_H__
