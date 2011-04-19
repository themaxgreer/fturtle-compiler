;
; sierpinski.ll
; LLVM assemby example
;
; compile (creates sierpinski.bc)
;   llvm-as sierpinski.ll
; create native assembly source sierpinski.s and assemble into .o
;   llc sierpinski.bc
;   as sierpinski.s
; create C source and compile
;   llc sierpinski.bc -o sierpinski.c -march=c
;   gcc -c sierpinski.c
; 
; future: use lli (LLVM execution engine) to execute code!
;

declare i32 @rotate(double)
declare i32 @move(double)

@max_depth = internal constant i32 5
@pi = internal constant double 3.141000e+00
@dist = internal constant double 1.570500e+00

declare i32 @B(i32)

define i32 @A(i32 %depth) {
entry:
  %0 = icmp sgt i32 %depth, 0
  br i1 %0, label %bb0, label %bb3

bb0:                                              
  %1 = add nsw i32 %depth, -1                    
  %2 = call i32 @B(i32 %1)          
  %3 = call i32 @rotate(double -6.000000e+01) 
  %4 = icmp sgt i32 %1, 0                        
  br i1 %4, label %bb1, label %bb2

bb1:                                            
  %5 = add nsw i32 %depth, -2                    
  %6 = call i32 @B(i32 %5)          
  %7 = call i32 @rotate(double -6.000000e+01) 
  %8 = call i32 @A(i32 %5)          
  %9 = call i32 @rotate(double -6.000000e+01) 
  %10 = call i32 @B(i32 %5)         
  br label %A.exit

bb2:                                           
  %11 = load double* @dist, align 8              
  %12 = call i32 @move(double %11)  
  br label %A.exit

A.exit:                                          
  %13 = call i32 @rotate(double -6.000000e+01) 
  %14 = call i32 @B(i32 %1)         
  ret i32 %14

bb3:                                             
  %15 = load double* @dist, align 8              
  %16 = call i32 @move(double %15)  
  ret i32 %16
}
