function H = getH(Xi)

global I2 T Xnip Ynip Znip options;

deltak = 20;
deltas = 2;
oo = Xi';

    % Интегрирование с начальными
    oo = [oo(1) oo(2) oo(3) oo(4) oo(5) oo(6)];
    [T1,Xo] = ode45(@Model,T,oo,options);
    
    % Интегрирование с начальными X+
    oo1p = [oo(1)+deltak oo(2) oo(3) oo(4) oo(5) oo(6)];
    [T1,X1p] = ode45(@Model,T,oo1p,options);
    
    % Интегрирование с начальными X-
    oo1m = [oo(1)-deltak oo(2) oo(3) oo(4) oo(5) oo(6)];
    [T1,X1m] = ode45(@Model,T,oo1m,options);
    
    % Интегрирование с начальными Y+
    oo2p = [oo(1) oo(2)+deltak oo(3) oo(4) oo(5) oo(6)];
    [T1,X2p] = ode45(@Model,T,oo2p,options);
    
    % Интегрирование с начальными Y-
    oo2m = [oo(1) oo(2)-deltak oo(3) oo(4) oo(5) oo(6)];
    [T1,X2m] = ode45(@Model,T,oo2m,options);
    
    % Интегрирование с начальными Z+
    oo3p = [oo(1) oo(2) oo(3)+deltak oo(4) oo(5) oo(6)]; 
    [T1,X3p] = ode45(@Model,T,oo3p,options);
    
    % Интегрирование с начальными Z-
    oo3m = [oo(1) oo(2) oo(3)-deltak oo(4) oo(5) oo(6)];
    [T1,X3m] = ode45(@Model,T1,oo3m,options);
    
    % Интегрирование с начальными Vx+
    oo4p = [oo(1) oo(2) oo(3) oo(4)+deltas oo(5) oo(6)]; 
    [T1,X4p] = ode45(@Model,T,oo4p,options);
    
    % Интегрирование с начальными Vx-
    oo4m = [oo(1) oo(2) oo(3) oo(4)-deltas oo(5) oo(6)];
    [T1,X4m] = ode45(@Model,T,oo4m,options);
    
    % Интегрирование с начальными Vy+
    oo5p = [oo(1) oo(2) oo(3) oo(4) oo(5)+deltas oo(6)];
    [T1,X5p] = ode45(@Model,T,oo5p,options);
    
    % Интегрирование с начальными Vy-
    oo5m = [oo(1) oo(2) oo(3) oo(4) oo(5)-deltas oo(6)];
    [T1,X5m] = ode45(@Model,T,oo5m,options);
    
    % Интегрирование с начальными Vz+
    oo6p = [oo(1) oo(2) oo(3) oo(4) oo(5) oo(6)+deltas];
    [T1,X6p] = ode45(@Model,T,oo6p,options);
    
    % Интегрирование с начальными Vz-
    oo6m = [oo(1) oo(2) oo(3) oo(4) oo(5) oo(6)-deltas];
    [T1,X6m] = ode45(@Model,T,oo6m,options);
    
% Получение dfi/dx0

%     X1d = (X1p(:,1)-X1m(:,1))/(2*deltak);
%     Y1d = (X1p(:,2)-X1m(:,2))/(2*deltak);
%     Z1d = (X1p(:,3)-X1m(:,3))/(2*deltak);

    for q=1:1:length(I2)
        k = I2(q);
        X1d = (X1p(k,1)-X1m(k,1))/(2*deltak);
        Y1d = (X1p(k,2)-X1m(k,2))/(2*deltak);
        Z1d = (X1p(k,3)-X1m(k,3))/(2*deltak);
        d = sqrt((Xo(k,1)-Xnip(k))^2+((Xo(k,2)-Ynip(k))^2+(Xo(k,3)-Znip(k))^2));
        X1f =(Xo(k,1)-Xnip(k))/d;
        Y1f =(Xo(k,2)-Ynip(k))/d;
        Z1f =(Xo(k,3)-Znip(k))/d;
        fx1(q) = X1f*X1d + Y1f*Y1d + Z1f*Z1d;
    end
    h1 = fx1';
     
    for q=1:1:length(I2)
        k = I2(q);
        X2d = (X2p(k,1)-X2m(k,1))/(2*deltak);
        Y2d = (X2p(k,2)-X2m(k,2))/(2*deltak);
        Z2d = (X2p(k,3)-X2m(k,3))/(2*deltak);
        d = sqrt((Xo(k,1)-Xnip(k))^2+((Xo(k,2)-Ynip(k))^2+(Xo(k,3)-Znip(k))^2));
        X2f =(Xo(k,1)-Xnip(k))/d;
        Y2f =(Xo(k,2)-Ynip(k))/d;
        Z2f =(Xo(k,3)-Znip(k))/d;     
        fx2(q) = X2f*X2d + Y2f*Y2d + Z2f*Z2d;
    end
    h2 = fx2';
     
    for q=1:1:length(I2)
        k = I2(q);
        X3d = (X3p(k,1)-X3m(k,1))/(2*deltak);
        Y3d = (X3p(k,2)-X3m(k,2))/(2*deltak);
        Z3d = (X3p(k,3)-X3m(k,3))/(2*deltak);
        d = sqrt((Xo(k,1)-Xnip(k))^2+((Xo(k,2)-Ynip(k))^2+(Xo(k,3)-Znip(k))^2));
        X3f =(Xo(k,1)-Xnip(k))/d;
        Y3f =(Xo(k,2)-Ynip(k))/d;
        Z3f =(Xo(k,3)-Znip(k))/d;     
        fx3(q) = X3f*X3d + Y3f*Y3d + Z3f*Z3d;
    end
    h3 = fx3';
     
    for q=1:1:length(I2)
        k = I2(q);
        X4d = (X4p(k,1)-X4m(k,1))/(2*deltas);
        Y4d = (X4p(k,2)-X4m(k,2))/(2*deltas);
        Z4d = (X4p(k,3)-X4m(k,3))/(2*deltas);
        d = sqrt((Xo(k,1)-Xnip(k))^2+((Xo(k,2)-Ynip(k))^2+(Xo(k,3)-Znip(k))^2));
        X4f =(Xo(k,1)-Xnip(k))/d;
        Y4f =(Xo(k,2)-Ynip(k))/d;
        Z4f =(Xo(k,3)-Znip(k))/d;     
        fx4(q) = X4f*X4d + Y4f*Y4d + Z4f*Z4d;
    end
    h4 = fx4';
     
    for q=1:1:length(I2)
        k = I2(q);
        X5d = (X5p(k,1)-X5m(k,1))/(2*deltas);
        Y5d = (X5p(k,2)-X5m(k,2))/(2*deltas);
        Z5d = (X5p(k,3)-X5m(k,3))/(2*deltas);
        d = sqrt((Xo(k,1)-Xnip(k))^2+((Xo(k,2)-Ynip(k))^2+(Xo(k,3)-Znip(k))^2));
        X5f =(Xo(k,1)-Xnip(k))/d;
        Y5f =(Xo(k,2)-Ynip(k))/d;
        Z5f =(Xo(k,3)-Znip(k))/d;
        fx5(q) = X5f*X5d + Y5f*Y5d + Z5f*Z5d;
    end
    h5 = fx5';
    
    for q=1:1:length(I2)
        k = I2(q);
        X6d = (X6p(k,1)-X6m(k,1))/(2*deltas);
        Y6d = (X6p(k,2)-X6m(k,2))/(2*deltas);
        Z6d = (X6p(k,3)-X6m(k,3))/(2*deltas);
        d = sqrt((Xo(k,1)-Xnip(k))^2+((Xo(k,2)-Ynip(k))^2+(Xo(k,3)-Znip(k))^2));
        X6f =(Xo(k,1)-Xnip(k))/d;
        Y6f =(Xo(k,2)-Ynip(k))/d;
        Z6f =(Xo(k,3)-Znip(k))/d;     
        fx6(q) = X6f*X6d + Y6f*Y6d + Z6f*Z6d;
    end
    h6 = fx6';
    
    for q=1:1:length(I2)
    h7(q,1) = 1;
    end
     
    H = [h1 h2 h3 h4 h5 h6 h7];