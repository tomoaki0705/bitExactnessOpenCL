# bitExactnessOpenCL
The purpose of this code is to check the output of sincos function on each OpenCL capable device.

# reference board
For this document, ODROID-N2 and Firefly-RK3399 were used.
ODROID-N2 comes with Amlogic S922X which has Mali G52 as an iGPU
Firefly-RK3399 comes with Rockchip RK3399 which has Mali T860 as an iGPU

# dump result

```
$ diff -u odroid-sincos-result firefly-sincos-result
--- odroid-sincos-result        2020-04-05 00:50:32.895600700 +0900
+++ firefly-sincos-result       2020-04-05 01:03:55.325130200 +0900
@@ -1,15 +1,15 @@
-00000000: 00000000 3c0ef9be 3c8ef859 3cd6710b  .......<Y..<.q.<
-00000010: 3d0ef2c6 3d32aa3e 3d565e3b 3d7a0e09  ...=>.2=;^V=..z=
-00000020: 3d8edc7b 3da0af2a 3db27eb6 3dc44ac7  {..=*..=.~.=.J.=
+00000000: 00000000 3c0ef9be 3c8ef859 3cd6710a  .......<Y..<.q.<
+00000010: 3d0ef2c6 3d32aa3e 3d565e3b 3d7a0e08  ...=>.2=;^V=..z=
+00000020: 3d8edc7b 3da0af2a 3db27eb5 3dc44ac7  {..=*..=.~.=.J.=
 00000030: 3dd61305 3de7d716 3df996a2 3e05a8a9  ...=...=...=...>
-00000040: 3e0e8365 3e175b59 3e20305c 3e29023d  e..>Y[.>\0 >=.)>
-00000050: 3e31d0d4 3e3a9bf3 3e43636f 3e4c271b  ..1>..:>ocC>.'L>
-00000060: 3e54e6ce 3e5da259 3e665991 3e6f0c4d  ..T>Y.]>.Yf>M.o>
-00000070: 3e77ba60 3e8031cf 3e8483ee 3e88d378  `.w>.1.>...>x..>
+00000040: 3e0e8365 3e175b59 3e20305b 3e29023d  e..>Y[.>[0 >=.)>
+00000050: 3e31d0d3 3e3a9bf3 3e43636f 3e4c271b  ..1>..:>ocC>.'L>
+00000060: 3e54e6ce 3e5da259 3e665991 3e6f0c4c  ..T>Y.]>.Yf>L.o>
+00000070: 3e77ba5f 3e8031cf 3e8483ee 3e88d377  _.w>.1.>...>w..>
 00000080: 3e8d2057 3e916a76 3e95b1be 3e99f61c  W .>vj.>...>...>
 00000090: 3e9e377a 3ea275c1 3ea6b0de 3eaae8bc  z7.>.u.>...>...>
 000000a0: 3eaf1d43 3eb34e62 3eb77c01 3ebba60c  C..>bN.>.|.>...>
-000000b0: 3ebfcc70 3ec3ef16 3ec80de9 3ecc28d7  p..>...>...>.(.>
+000000b0: 3ebfcc70 3ec3ef15 3ec80de9 3ecc28d6  p..>...>...>.(.>
 000000c0: 3ed03fc9 3ed452ac 3ed8616c 3edc6bf3  .?.>.R.>la.>.k.>
 000000d0: 3ee0722f 3ee4740a 3ee87171 3eec6a50  /r.>.t.>qq.>Pj.>
 000000e0: 3ef05e94 3ef44e27 3ef838f7 3efc1ef1  .^.>'N.>.8.>...>
@@ -106,43 +106,43 @@
 000000f0: 3f5db3d7 3f5c93ba 3f5b6f51 3f5a46a0  ..]?..\?Qo[?.FZ?
 00000100: 3f5919ae 3f57e880 3f56b31d 3f55798b  ..Y?..W?..V?.yU?
 00000110: 3f543bcf 3f52f9ef 3f51b3f3 3f5069e0  .;T?..R?..Q?.iP?
-00000120: 3f4f1bbd 3f4dc991 3f4c7361 3f4b1934  ..O?..M?asL?4.K?
+00000120: 3f4f1bbd 3f4dc990 3f4c7361 3f4b1934  ..O?..M?asL?4.K?
 00000130: 3f49bb13 3f485902 3f46f309 3f458931  ..I?.YH?..F?1.E?
 00000140: 3f441b7d 3f42a9f7 3f4134a6 3f3fbb90  }.D?..B?.4A?..??
 00000150: 3f3e3ebd 3f3cbe35 3f3b39ff 3f39b223  .>>?5.<?.9;?#.9?
 00000160: 3f3826a7 3f369795 3f3504f3 3f336eca  .&8?..6?..5?.n3?
 00000170: 3f31d522 3f303801 3f2e9772 3f2cf37b  ".1?.80?r..?{.,?
 00000180: 3f2b4c24 3f29a178 3f27f37c 3f26423a  $L+?x.)?|.'?:B&?
-00000190: 3f248dbb 3f22d606 3f211b25 3f1f5d1f  ..$?.."?%.!?.].?
+00000190: 3f248dbb 3f22d605 3f211b25 3f1f5d1f  ..$?.."?%.!?.].?
```

So many lines, so I skipped the detail, but the result shows that though the GPU comes from same vendor (Arm), the computation of sin/cos is different
The floating point arithmetic is not-bit exact and thus, rounding error could happen.
