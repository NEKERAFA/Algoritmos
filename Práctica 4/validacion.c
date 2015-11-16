testinicializarmonticulo(){
   monticulo m;

   printf("Test inicializar_monticulo\n");
   inicializar_monticulo(&m);

   if(m.ultimo == -1){
      printf("Test superado\n");
   } else {
      printf("*************TEST NO SUPERADO*************\n");
   }
}

testswap(){
   monticulo m;
   int valido = 1;

   printf("Test swap\n");

   inicializar_monticulo(&m);

   m.vector[0] = 4;
   m.vector[1] = 2;
   m.vector[2] = 3;
   m.vector[3] = 1;
   m.ultimo = 3;

   swap(&m,0,3);

   if(m.vector[0] != 1) valido = 0;
   if(m.vector[1] != 2) valido = 0;
   if(m.vector[2] != 3) valido = 0;
   if(m.vector[3] != 4) valido = 0;
   if(m.ultimo    != 3) valido = 0;
   
   if(valido){
      printf("Test superado\n");
   } else {
      printf("*************TEST NO SUPERADO*************\n");
   }

}

testflotar(){
   monticulo m;
   int valido = 1;

   printf("Test flotar\n");
   inicializar_monticulo(&m);
   
   m.vector[0] = 2;
   m.vector[1] = 3;
   m.vector[2] = 4;
   m.vector[3] = 5;
   m.vector[4] = 6;
   m.vector[5] = 1;
   m.ultimo = 5;
   
   flotar(&m,5);
   
   if(m.vector[0] != 1) valido = 0;
   if(m.vector[1] != 3) valido = 0;
   if(m.vector[2] != 2) valido = 0;
   if(m.vector[3] != 5) valido = 0;
   if(m.vector[4] != 6) valido = 0;
   if(m.vector[5] != 4) valido = 0;
   if(m.ultimo    != 5) valido = 0;
   
   if(valido){
      printf("Test superado\n");
   } else {
      printf("*************TEST NO SUPERADO*************\n");
   }
}

testhundir(){
   monticulo m;
   int valido = 1;

   printf("Test hundir\n");
   inicializar_monticulo(&m);
   
   m.vector[0] = 6;
   m.vector[1] = 1;
   m.vector[2] = 2;
   m.vector[3] = 3;
   m.vector[4] = 4;
   m.vector[5] = 5;
   m.ultimo = 5;
   
   hundir(&m,1);
   
   if(m.vector[0] != 1) valido = 0;
   if(m.vector[1] != 3) valido = 0;
   if(m.vector[2] != 2) valido = 0;
   if(m.vector[3] != 6) valido = 0;
   if(m.vector[4] != 4) valido = 0;
   if(m.vector[5] != 5) valido = 0;
   if(m.ultimo    != 5) valido = 0;
   
   if(valido){
      printf("Test superado\n");
   } else {
      printf("*************TEST NO SUPERADO*************\n");
   }
}

testinsertar(){
   monticulo m;
   int valido = 1;

   printf("Test insertar\n");
   inicializar_monticulo(&m);

   insertar(&m,5);
   insertar(&m,3);
   insertar(&m,7);
   insertar(&m,0);
   insertar(&m,6);
   insertar(&m,8);
   insertar(&m,9);
   insertar(&m,2);
   insertar(&m,1);
   insertar(&m,4);

   if(m.vector[0]!=0) validacion = 0;
   if(m.vector[1]!=1) validacion = 0;
   if(m.vector[2]!=7) validacion = 0;
   if(m.vector[3]!=2) validacion = 0;
   if(m.vector[4]!=4) validacion = 0;
   if(m.vector[5]!=8) validacion = 0;
   if(m.vector[6]!=9) validacion = 0;
   if(m.vector[7]!=5) validacion = 0;
   if(m.vector[8]!=3) validacion = 0;
   if(m.vector[9]!=6) validacion = 0;
   if(m.ultimo != 9) validacion = 0;

   if(valido){
      printf("Test superado\n");
   } else {
      printf("*************TEST NO SUPERADO*************\n");
   }
}
testeliminarmenor(){
   monticulo m;
   int valido = 1;

   printf("Test eliminar_menor\n");

   insertar(&m,5);
   insertar(&m,3);
   insertar(&m,7);
   insertar(&m,0);
   insertar(&m,6);
   insertar(&m,8);
   insertar(&m,9);
   insertar(&m,2);
   insertar(&m,1);
   insertar(&m,4);

   if(eliminar_menor(&m)!=0) validacion = 0;
   if(eliminar_menor(&m)!=1) validacion = 0;
   if(eliminar_menor(&m)!=2) validacion = 0;
   if(eliminar_menor(&m)!=3) validacion = 0;
   if(eliminar_menor(&m)!=4) validacion = 0;
   if(eliminar_menor(&m)!=5) validacion = 0;
   if(eliminar_menor(&m)!=6) validacion = 0;
   if(eliminar_menor(&m)!=7) validacion = 0;
   if(eliminar_menor(&m)!=8) validacion = 0;
   if(eliminar_menor(&m)!=9) validacion = 0;
   if(m.ultimo != 0) validacion = 0;
   
   if(valido){
      printf("Test superado\n");
   } else {
      printf("*************TEST NO SUPERADO*************\n");
   }
}
testcrearmonticulo(){
   monticulo m;
   int v[10] = {5,3,7,0,6,8,9,2,1,4};
   int valido = 1;

   printf("Test crear_monticulo");
   inicializar_monticulo(&m);

   crear_monticulo(v,10,&m);

   if(m.vector[0]!=0) validacion = 0;
   if(m.vector[1]!=1) validacion = 0;
   if(m.vector[2]!=7) validacion = 0;
   if(m.vector[3]!=2) validacion = 0;
   if(m.vector[4]!=4) validacion = 0;
   if(m.vector[5]!=8) validacion = 0;
   if(m.vector[6]!=9) validacion = 0;
   if(m.vector[7]!=5) validacion = 0;
   if(m.vector[8]!=3) validacion = 0;
   if(m.vector[9]!=6) validacion = 0;
   if(m.ultimo != 9) validacion = 0;

   if(valido){
      printf("Test superado\n");
   } else {
      printf("*************TEST NO SUPERADO*************\n");
   }
}

testear(){
   testinicializarmonticulo();
   testswap();
   testflotar();
   testhundir();
   testinsertar();
   testeliminarmenor();
   testcrearmonticulo();
}

//OJO EN COTAS Y EN MEDICIONES ANOMALAS