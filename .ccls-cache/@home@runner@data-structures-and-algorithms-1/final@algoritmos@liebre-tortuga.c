

SList lyt(SList lista) {
  SList liebre = lista;
  SList tortuga = lista;

  int ciclo = 0;
  while (liebre != NULL && liebre->sig != NULL && !ciclo) {
    tortuga = tortuga->sig;
    liebre = liebre->sig->sig;
    if (tortuga == liebre)
      ciclo = 1;
  }

  if (!ciclo)
    return NULL;
  else {
    liebre = lista;
    while (liebre != tortuga) {
      tortuga = tortuga->sig;
      liebre = liebre->sig;
    }
  }

  return liebre;
}