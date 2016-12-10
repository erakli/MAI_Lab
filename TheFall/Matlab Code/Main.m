clear all
close all
clc

global mu; % Лучше объявить эту перемнную глобальной, чтобы использовать в функции правых частей ДУ
mu = 398600.436e9; % Корректное значение
i = 68*3.1415/180;
% hper = 210000
% hap = 470000
hper = 630000;
hap = 1410000;
Re = 6371000;

a = (hap + hper + 2*Re)/2;
e = (hap - hper)/(hap + hper + 2*Re);
p = a*(1 - e^2);
n = sqrt(mu/a^3);
t = 1;
M = n*t;
tet = M + (2*e-e^3/4)*sin(M) + 5/4*e^2*sin(2*M) + 13/12*e^3*sin(3*M);

r = p/(1+e*cos(tet));
Vr = sqrt(mu/p)*e*sin(tet);
Vn = sqrt(mu/p)*(1+e*cos(tet));

rvekt = [r;0;0];
vvekt = [Vr;Vn;0];

OMG = 25*pi/180; % Долгота восходящего узла орбиты, можно выбрать проивольно
omg = 15*pi/180; % Широта перицентра (выбрал произвольно)
u = omg+tet; % Аргумент широты
i = 45*pi/180; % Наклонение орбиты, выбирается произвольно
A = [cos(u)*cos(OMG)-sin(u)*sin(OMG)*cos(i) -sin(u)*cos(OMG)-cos(u)*sin(OMG)*cos(i) sin(i)*sin(OMG);
    cos(u)*sin(OMG)+sin(u)*cos(OMG)*cos(i) -sin(u)*sin(OMG)+cos(u)*cos(OMG)*cos(i) -sin(i)*cos(OMG);
    sin(u)*sin(i) cos(u)*sin(i) cos(i)]

X0 = A*rvekt;
V0 = A*vvekt;
o = [X0(1) X0(2) X0(3) V0(1) V0(2) V0(3)];

% Переходим к интегрированию

% [T,X] = ode45(@vdp1000,[0:10:5990],o);
% [T,X] = ode45(@vdp1000,[0:10:29990],o,1e-18);
global options;
options = odeset('RelTol',1e-4);
global T;
[T,X] = ode45(@Model, [0:10:29990], o, options);

%График любой компоненты от времени

%figure
%plot (T,X(:,1)); grid on

%Вид траектории в проекциях на плоскости x0y, x0z, y0z

%figure
%plot (X(:,1),X(:,2),   X(:,1),X(:,3),   X(:,2),X(:,3))

Xxsp = [X(:,1) X(:,2) X(:,3)];

% Перевод геодезических координат НИП в xyz

% t1 = {0:0.1:1000}
shirota = 57*pi/180;
dolgota = 38*pi/180;
h = 750;
Omega = 7.292115*10^-5 % А вот здесь действительно угловая скорость вращения Земли
Sg = Omega*T;
Xnip0 = (Re+h)*cos(shirota)*cos(dolgota);
Ynip0 = (Re+h)*cos(shirota)*sin(dolgota);
Znip0 = (Re+h)*sin(shirota);
global Xnip Ynip Znip;
Xnip = (Re+h)*cos(shirota)*cos(dolgota + Sg);
Ynip = (Re+h)*cos(shirota)*sin(dolgota + Sg);
Znip = (Re+h)*sin(shirota)+Sg.*0;
% Xnipp = Xnip';
% Ynipp = Ynip';
% Znipp = Znip';
Xxnip = [Xnip  Ynip  Znip];

% figure
% plot (t1,Xnip)
% grid on
% figure
% plot (t1,Ynip)
% grid on
% figure
% plot (t1,Znip)
d_eta = 1;
dcherta = 30;
global I2;
k = 1;
% Истинные измерения
for n = 1:1:length(T)

    R = Xxsp(n,:) - Xxnip(n,:);
    kv = Xxnip(n,:)*R' / norm(Xxnip(n,:)) / norm(R);

    p = acosd(kv);
    
    if abs(p) <= 70
           d = sqrt((X(n,1) - Xnip(n))^2 + (X(n,2) - Ynip(n))^2 + (X(n,3) - Znip(n))^2);
           deltad = sqrt(d_eta)*randn();
           Y(k,1) = d + dcherta + deltad;
           I2(k,1) = n; % Индексы моментов измерений
           k = k+1;
    end
end
%   plot (Y(:,1)); grid on

% Ковариационная матрица ошибок измерений

I = eye(length(I2));
D = I*d_eta;
Dinv = inv(D); % обратная матрица D

 Xi(:,1) = [o(1)-1e2; o(2)+1e3; o(3)-1e3; o(4)+1e1; o(5)-1e1; o(6)+1e1; 0];
 Eps = [1; 1; 1; 1e-2; 1e-2; 1e-2; 1e-4];
 for i=2:1:15
    H = getH(Xi(:,i-1));
    Fi = getMeasure(Xi(:,i-1));
    K = (H'*Dinv*H)^(-1);
    Xi(:,i) = Xi(:,i-1) + K*(H')*Dinv*(Y-Fi);

    if (abs(Xi(:,i) - Xi(:,i-1)) < Eps)
        break;
    end;
 end
 
 figure()
 plot (Xi(1,:))
 grid on
 
 figure()
 plot (Xi(2,:))
 grid on
 
 figure()
 plot (Xi(3,:))
 grid on
 
 figure()
 plot (Xi(7,:))
 grid on
 