function Fi = getMeasure(Xi)
global I2 T Xnip Ynip Znip options;

o = [Xi(1) Xi(2) Xi(3) Xi(4) Xi(5) Xi(6)];
[T1, Xfi] = ode45(@Model, T, o, options);
    
  for q=1:1:length(I2)   
     k = I2(q);
     Fi(q,1) = sqrt((Xfi(k,1)-Xnip(k))^2 + (Xfi(k,2)-Ynip(k))^2 + (Xfi(k,3)-Znip(k))^2)+Xi(7);
  end