function C = paraPID_pp(Ctype,P,p1,p2,p3,p4)
if order(P) ~= 2
    error('Nominal plant should be second order');
end
if nargin < 4 %?“ü?—Ê“I˜¢”
   p2 = p1; 
   p3 = p1; 
   p4 = p1; 
end

s = tf('s');
syms a2 a1 a0 b2 b1 x
[num1,den1] = tfdata(P,'v');
Pnew=double(poly2sym(num1,x))/(poly2sym(den1,x));
digits(4);
Pnew=vpa(Pnew);

switch Ctype
    case 'pid'
        cl=1/((s+p1)*(s+p2)*(s+p3)*(s+p4));
        [num2,den2]=tfdata(cl,'v');
        Dcl1=den2;
        C=(a2*x^2+a1*x+a0)/(b2*x^2+b1*x);
        CL=(a2*x^2+a1*x+a0)*(double(poly2sym(num1,x)))+(b2*x^2+b1*x)*(poly2sym(den1,x));
        digits(4);
        CL=vpa(CL);
        Dcl2=fliplr(coeffs(CL,x));
        [a0,a1,a2,b1,b2]=solve(Dcl2(1)==Dcl1(1),Dcl2(2)==Dcl1(2),Dcl2(3)==Dcl1(3),Dcl2(4)==Dcl1(4),Dcl2(5)==Dcl1(5));
        K_1=double(a2);
        K_2=double(a1);
        K_3=double(a0);
        K_4=double(b2);
        K_5=double(b1);
      C=minreal((K_1*s^2 + K_2*s + K_3)/(K_4*s^2 +K_5*s));
%        C=(a2*s^2+a1*s+a0)/(b2*s^2+b1*s);
%       C = pid(C);  
    case 'pi'
        cl=1/((s+p1)*(s+p2));
        [num,den2]=tfdata(cl,'v');
         Dcl1=den2;
        C=(a1*x+a0)/(b1*x);
        CL=(a1*x+a0)*(double(poly2sym(num1,x)))+(b1*x)*(poly2sym(den1,x)/x);
        digits(4);
        CL=vpa(CL);
        Dcl2=fliplr(coeffs(CL,x));
        [a0,a1,b1]=solve(Dcl2(1)==Dcl1(1),Dcl2(2)==Dcl1(2),Dcl2(3)==Dcl1(3));
         K_1=double(a1);
         K_2=double(a0);
         K_3=double(b1);
        C=minreal((K_1*s+ K_2)/(K_3*s));
%         C=(a2*s^2+a1*s+a0)/(b2*s^2+b1*s);
end
end

%% previous code
% p2z=poly2sym(num);
% p2p=poly2sym(den);
% clop=fliplr(coeffs(eq,x));% ‹ŽæŒn”
% zp2=sym2poly(p2z);
% pp2=sym2poly(p2p);

% a1=clop(4)/zp2;
% a2=clop(5)/zp2;
% b0=clop(1)/pp2(1);
% b1=clop(2)/pp2(1)-pp2(2)*b0/pp2(1);
% a0=clop(3)/zp2-pp2(2)*b1/zp2;
% K = double([a0 a1 a2 b0 b1]); % C‰ü?—Ê?Œ^
% C=(K(1)*s^2 + K(2)*s + K(3))/(K(4)*s^2 +K(5)*s);
% C = pid(C);
