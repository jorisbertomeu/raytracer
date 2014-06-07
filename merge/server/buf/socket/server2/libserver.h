/*
** libserver.h for LibServer in /home/jobertomeu/Work/rush4/server/src
** 
** Made by Joris Bertomeu
** Login   <jobertomeu@epitech.net>
** 
** Started on  Sat May 10 17:04:26 2014 Joris Bertomeu
** Last update Sun May 18 15:38:05 2014 Joris Bertomeu
*/

#ifndef LIBSERVER_H_
#define LIBSERVER_H_

# include <stdio.h>
# include <sys/types.h>
# include <sys/select.h>
# include <signal.h>
# include <errno.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <fcntl.h>
# include <string.h>
# include <stdlib.h>
# include <sys/time.h>
# include <sys/types.h>
# include <unistd.h>

typedef struct s_clients	t_clients;
struct				s_clients
{
  int				active;
  int				id;
  int				idsock;
  int				fd;
  struct sockaddr_in		cli_addr;
};

typedef struct s_libserver t_libserver;
struct s_libserver
{
  int			sockfd;
  int			newsockfd;
  int			portno;
  int			clilen;
  int			n;
  char			buffer[4096];
  struct sockaddr_in	serv_addr;
  struct sockaddr_in	cli_addr[6];
  int			id_client;
  t_clients		clients[6];
  int			fds[6];
  int			fdtmp;
  int			current_id_fd;
};

#endif /* LIBSERVER_H_ */
