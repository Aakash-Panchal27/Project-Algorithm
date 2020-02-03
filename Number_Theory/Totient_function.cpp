// phi(i)*phi(j) = phi(i*j)-----------------> if i and j are relatively prime.
// phi(i)*phi(j)*d/phi(d) = phi(i*j) -------------> if gcd(i,j) == d then this.




// Two Implementation

ll phi(ll n)
{
	ll ans=n,i=2,l=n;
	while(i*i<=n)
	{
		if(n%i==0)
		{
			while(n%i==0)n/=i;
			ans-=ans/i;
		}
		i++;
	}
	if(n>1)ans-=ans/n;
	return ans;
}

// Phi values for all 0 to n
vector<ll> phi0Ton(ll n)
{
	vector<ll> phis(n+1);
	for(int i=1;i<n+1;i++)
		phis[i]=i;
		
	for(int i=2;i<=n;i++)
	{
		if(phis[i]==i){
			phis[i]--;
			for(int j=2*i;j<=n;j+=i)
			{
				phis[j]-=phis[j]/i;
			}
		}
	}
	return phis;
}
