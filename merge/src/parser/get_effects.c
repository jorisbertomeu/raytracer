/*
** get_effects.c for Parser RT in /home/martel_c/rendu/RT/raytracer/src/parser/parser2
**
** Made by martelliere
** Login   <martel_c@epitech.net>
**
** Started on  Thu Jun  5 18:09:01 2014 martelliere
** Last update Sat Jun  7 15:57:37 2014 martelliere
*/

#include	"parser.h"

void		aff_esyntax(t_parser *parser)
{
  fprintf(stderr, "Syntax error line %d.\n", parser->line);
  exit(EXIT_FAILURE);
}

void		check_constant(t_parser *parser, float nb)
{
  if (nb < 0.0 || nb > 1.0)
    {
      fprintf(stderr, "Error line %d: this value %f must be between 0 \
and 1 included.\n", parser->line, nb);
      exit(EXIT_FAILURE);
    }
}

float		get_brill(t_parser *parser)
{
  float		brill;

  parser->line++;
  parser->n++;
  if (parser->tab[parser->n] != NULL &&
      strcmp(strlower(parser->tab[parser->n]), "<brill>") == 0)
    {
      parser->n++;
      parser->line++;
      if (parser->tab[parser->n] != NULL && parser->tab[parser->n][0] == '<' &&
          parser->tab[parser->n][strlen(parser->tab[parser->n]) - 1] == '>')
	brill = atof(&(parser->tab[parser->n][1]));
      else
	aff_esyntax(parser);
      check_constant(parser, brill);
    }
  else
    {
      fprintf(stderr, "Syntax error line %d: \"<brill>\" missing.\n",
	      parser->line);
      exit(EXIT_FAILURE);
    }
  return (brill);
}

float		get_opacity(t_parser *parsr)
{
  float		opacity;

  parsr->line++;
  parsr->n++;
  if (parsr->tab[parsr->n] != NULL &&
      strcmp(strlower(parsr->tab[parsr->n]), "<opacity>") == 0)
    {
      parsr->n++;
      parsr->line++;
      if (parsr->tab[parsr->n] != NULL && parsr->tab[parsr->n][0] == '<' &&
          parsr->tab[parsr->n][strlen(parsr->tab[parsr->n]) - 1] == '>')
        opacity = atof(&parsr->tab[parsr->n][1]);
      else
	aff_esyntax(parsr);
      check_constant(parsr, opacity);
    }
  else
    {
      fprintf(stderr, "Syntax error line %d: \"<opacity>\" missing.\n",
	      parsr->line);
      exit(EXIT_FAILURE);
    }
  return (opacity);
}

float		get_reflexion(t_parser *parser)
{
  float		reflexion;

  parser->line++;
  parser->n++;
  if (parser->tab[parser->n] != NULL &&
      strcmp(strlower(parser->tab[parser->n]), "<reflexion>") == 0)
    {
      parser->n++;
      parser->line++;
      if (parser->tab[parser->n] != NULL && parser->tab[parser->n][0] == '<' &&
          parser->tab[parser->n][strlen(parser->tab[parser->n]) - 1] == '>')
	reflexion = atof(&(parser->tab[parser->n][1]));
      else
	aff_esyntax(parser);
      check_constant(parser, reflexion);
    }
  else
    {
      fprintf(stderr, "Syntax error line %d: \"<reflexion>\" missing.\n",
	      parser->line);
      exit(EXIT_FAILURE);
    }
  return (reflexion);
}
