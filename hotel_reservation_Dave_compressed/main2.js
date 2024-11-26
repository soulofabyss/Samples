class room{            // class room which uses an arry as datatype
    constructor(j)
    {
        
        this.days=[j];
        for(let i=0;i<=j;i++)
        {
            this.days[i]= 0;
        }
        
    }
    assign(k)
    {
        this.days[k]= 1  ;
    }
    check(k)
    {
        if(this.days[k]==0)
        {
            return(0);
        }
        else
        {
           return(1);
        }
    }

}

function isfree(m,n,no_of_rooms,no_days)//function to check if there are any free rooms available at the required time and return the free room number
{
    
    f2=0;
    for(let i=0;i<no_of_rooms;i++)
    { 
        f1=0;
        //console.log("loop1");
        for(let j=m ;j<=n ; j++ )
        {
          //  console.log("loop2",j);
            if(hotel[i].check(j)==1)
            {
            //    console.log("loop3");
                f1=1;
                break;
            }
            
        }

        if(f1==0)
        {
            
        return i;
        }
    }
    return(-1);
}
function reserve(x,y,z)//function to reserve the room for that particular day
{
    for(let i=x;i<=y;i++)
    {
    hotel[z].assign(i);
    }
}
function main(x,y,no_of_rooms,no_days)//function to check vacancy and return declined if there is no vacancy
{
    if ( x<0 || y<0  || x>no_days || y>no_days )
    {
        console.log(x);
        console.log(y);
        console.log(no_days);
        return("declined");
    }

   f1 = isfree(x,y,no_of_rooms,no_days);
   if (f1==-1)
   {   // console.log("llll");
       return("Declined");
   }
   reserve(x,y,f1);
   return("Accepted")
}


x=1000;
y=365;
var fl=0;
var s="\n";
var hotel = new Array();
for (let i = 0; i < x; i++)
{
    hotel.push(new room(y));
}    



console.log(hotel);

//function showhotel(m=x,n=y,,no_of_rooms,no_days)

    


function bookhotel() //function to book the room in the hotel takes in user input and give output
{
    
    t1=document.getElementById("sdate").value;
    t2=document.getElementById("edate").value;
    if(t1==""||t2=="")
    {
           
        alert("Please enter  for both number of rooms and number of days ")
        throw"Please enter for both number of rooms and number of days ";
    }
    
    sdate= parseInt(document.getElementById("sdate").value);
    
    
    edate = parseInt(document.getElementById("edate").value);
    
    
    
    
    if(sdate>edate)
    {
        alert("Start date cant be higher than the end date")
        throw"Start date cant be higher than the end date";
    }
    fl++;
    
    bookingresult = main(sdate,edate,x,y);
    s=s+"<BR>"+"Booking"+fl+"):&nbsp&nbsp&nbsp&nbsp"+sdate+" &nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp"+edate+"&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp "+bookingresult; 
    
    console.log("booking "+fl+bookingresult);
    s=s+"<br>";
    document.getElementById("bookingresult").innerHTML =s ;
    console.log(hotel);    
    
 }
