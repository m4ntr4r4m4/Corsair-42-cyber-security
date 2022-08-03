# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    README.md                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/03 16:38:37 by ahammoud          #+#    #+#              #
#    Updated: 2022/08/03 17:02:22 by ahammoud         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


coRSAir Documentation:
	
	If we have two certificates generated in a system whose random number generator
	is weak and therefore in which the entropy is minimum... This may have increase the
	probability of repetitions of prime numbers during different generations, thus it might
	have been the case in which two modules share the same factor p or q.
		[n1 = p1 · q1] [n2 = p1 · q2]




		In This tools we are trying to use this vulnerabilty to crack the RSA private key from the public key.

		We know that Modulus of the first key  is N1 = P1 * Q1 
		& the Modulus of the 2nd Key is N2 = P2 * Q2
		and P or The Q are the same in both keys.
		to exploit this vulnerabilty we calculate the Great Common Diviser
		gcd(N1, N2) = a prime number shared between the two keys.
						P = gcd
		we calculate the 2nd prime by divising the modulus by the gcd.
						Q = mod / gcd
		the public exponent is a number we can get it from the public key.
						pubexp
		the next steps is to calculate the private exponent:
						privexp = (1 / pubkey) mod φ
						with φ = (P - 1) (Q - 1)
		after that we calculate the exponent e1:
						e1 = privexp mod (P - 1)
		after that we calculate the exponent e2:
						e2 = privexp mod (Q - 1)
		and then we calculate the coefficient:
						coeff = (1 / Q) mod P
		now we have all the  variable we need to create the Private key of this public key.

	
		in our code we create a RSA Object and we give it these values, and then we write the RSA Object to file. YaY we cracked a RSA public key.

One of the difficulties of this project is to handle bignumber and it's arethmetics.

	For this we are using the BIGNUM *num type from Openssl lib.
	the lib provides many function to do the arethmetics on bignumber like  +, -, *, /, % ...
