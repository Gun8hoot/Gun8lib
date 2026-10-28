
#include "gun8lib.h"

#include <string>
#include <stdexcept>
#include <unistd.h>
#include <pwd.h>

static	const std::string	get_username(void)
{
	uid_t	uid = getuid();
	passwd	*data = getpwuid(uid);

	if (!data || !data->pw_name)
		throw (std::runtime_error("Failed to get the username"));
	return (std::string(data->pw_name));
}

std::string	&expand(std::string &path)
{
	const std::string username = get_username();

	if (path.rfind("~/", 0) == 0) // Pas ouf ne marche pas avec juste "~"
	{
		path.erase(0, 1);
		path = "/home/" + username + path;
	}
	return (path);
}
