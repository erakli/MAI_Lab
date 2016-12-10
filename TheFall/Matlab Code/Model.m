function dx = Model(t,x)
global mu;
r3 = sqrt(x(1)^2+x(2)^2+x(3)^2)^3;
dx = zeros(6,1);
dx(1) = x(4);
dx(2) = x(5);
dx(3) = x(6);
dx(4) = -mu*x(1)/r3;
dx(5) = -mu*x(2)/r3;
dx(6) = -mu*x(3)/r3;