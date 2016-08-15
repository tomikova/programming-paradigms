use warnings;
use Try::Tiny;

package Person;
sub new
{
	my $class = shift;
	my $self = 
	{
		code   => shift,
		name     => shift,
		surname => shift,
		points  => shift,
	};
	bless $self, $class;
	return $self;
}

sub name_contains
{
	if(scalar(@_)>1)
	{
	    my @newOne=qw();
	    my $size=scalar(@_);
	    for($i=0;$i<$size-1;$i++)
	    {
		    if(index($_[$i]->{name}, $_[$size-1]) != -1)
		    {
		   	    push(@newOne,$_[$i]);
		    }
	    }
	    return @newOne;
       }
       else
       {
       	    die "Empty list";
       }
}

sub points_greater_than
{       if(scalar(@_)>1)
	{
	    my @newOne=qw();
	    my $size=scalar(@_);
	    for($i=0;$i<$size-1;$i++)
	    {
		    if($_[$i]->{points} > $_[$size-1])
		    {
			    push(@newOne,$_[$i]);
		    }
	    }
	    return @newOne;
       }
       else
       {
       	    die "Empty list";
       }
}

sub surname_name
{
	if(scalar(@_)>0)
	{
	    my @newOne=qw();
	    my $size=scalar(@_);
	    for($i=0;$i<$size;$i++)
	    {
		    my $string = $_[$i]->{surname}." ".$_[$i]->{name};
		    push(@newOne,$string);
	    }
	    return @newOne;
        }
        else
        {
            die "Empty list";
        }
}

sub points_surname
{
	if(scalar(@_)>0)
	{
	    my @newOne=qw();
	    my $size=scalar(@_);
	    for($i=0;$i<$size;$i++)
	    {
		    my $string = $_[$i]->{points}." ".$_[$i]->{surname};
		    push(@newOne,$string);
	    }
	    return @newOne;
        }
        else
        {
            die "Empty list";
        }
}

sub sum_points
{
	if(scalar(@_)>0)
	{
	    my $sum=0;
	    my $size=scalar(@_);
	    for($i=0;$i<$size;$i++)
	    {
		    $sum=$sum+$_[$i]->{points};
	    }
	    return $sum;
        }
        else
        {
            die "Empty list";
        }
}

sub take_greater_points
{
	if(scalar(@_)>0)
	{
	    my $max=0;
	    my $size=scalar(@_);
	    for($i=0;$i<$size;$i++)
	    {
		    if($_[$i]->{points}>$max)
		    {
			    $max=$_[$i]->{points};
		    }
	    }
	    return $max;
       }
       else
       {
       	    die "Empty list";
       }
}

sub read_data
{
	my $file = 'data.txt';
        open my $info, $file or die "Can't open file $file";

        my @people=qw();
        while( my $line = <$info>)  
        {  
             my @row=split(' ', $line);
             my $object = new Person($row[0],$row[1],$row[2],$row[3]); 
             push(@people,$object); 
        }
        close $info;
        return @people;
}

sub _where
{       try
        {
	    my @newOne=qw();
	    my $size=scalar(@_);
	    for($i=0;$i<$size-2;$i++)
	    {
		    push(@newOne,$_[$i]);	
	    }
	
	    my @result = $_[$size-1](@newOne,$_[$size-2]);
	    return @result; 
       }
       catch
       {
       	    warn "caught error: $_";
       };
}

sub _select
{
	try
	{
	    my @newOne=qw();
	    my $size=scalar(@_);
	    for($i=0;$i<$size-1;$i++)
	    {
		    push(@newOne,$_[$i]);	
	    }
	
	    my @result = $_[$size-1](@newOne);
	    return @result; 
        }
        catch
        {
       	    warn "caught error: $_";
        };
}

sub _aggregate
{
	try
	{
	    my @newOne=qw();
	    my $size=scalar(@_);
	    for($i=0;$i<$size-1;$i++)
	    {
		    push(@newOne,$_[$i]);	
	    }
	    my $result = $_[$size-1](@newOne);
	    return $result
        }
        catch
        {
       	    warn "caught error: $_";
        };
}

sub main
{
	my @podaci=read_data();
	
	my @result1a=_where(@podaci,'1',"name_contains");
	
	my $result6a=_aggregate(@result1a,"sum_points");
	my $result6b=_aggregate(@result1a,"take_greater_points");
	
	my $prosjek=$result6a/scalar(@result1a);
	
	my @result1b=_where(@result1a,$prosjek,"points_greater_than");
	
	my @result4a=_select(@result1b,"surname_name");
	my @result4b=_select(@result1b,"points_surname");
	
	print "Students whose name contains the symbol '1':\n";
	for($i=0;$i<scalar(@result1a);$i++)
	{
		print $result1a[$i]->{code},"\n";
		print $result1a[$i]->{name},"\n";
		print $result1a[$i]->{surname},"\n";
		print $result1a[$i]->{points},"\n";
	}
	
	print "\nThe sum of points of students:",$result6a,"\n";
	print "Max number of points:",$result6b,"\n";
	print "Avg number of points:",$prosjek,"\n";
	
	print "\nStudents with a score higher than average:\n";
	for($i=0;$i<scalar(@result1b);$i++)
	{
		print $result1b[$i]->{code},"\n";
		print $result1b[$i]->{name},"\n";
		print $result1b[$i]->{surname},"\n";
		print $result1b[$i]->{points},"\n";
	}
	
	print "\nsurname name:\n";
	for($i=0;$i<scalar(@result4a);$i++)
	{
		print $result4a[$i],"\n";
	}
	print "\npoints surname:\n";
	for($i=0;$i<scalar(@result4b);$i++)
	{
		print $result4b[$i],"\n";
	}
}

main();
