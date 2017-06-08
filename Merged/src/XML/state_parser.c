#ifndef		__XML_STATE_PARSER_C__
# define	__XML_STATE_PARSER_C__

# include	"XMLParser.h"

/*
** Get the text between to braces ( <xmpl> DATA GETED BY THIS FUNCTION </xmpl> )
*/
void		getTextData(int *i, char **tokens, XMLtree_parser *info)
{ 
  char		*tmp;

  while (tokens[*i] != NULL && tokens[*i][0] != '<')
    {
      if (is_a_token(tokens[*i], ">/\"=\'") == 0)
	{
	  tmp = mconcat((*info).content, tokens[*i]);
	  free((*info).content);
	  (*info).content = strdup(tmp);
	  free(tmp);
	}
      else
	{
	  tmp = mconcat((*info).content, " ");
	  free((*info).content);
	  (*info).content = strdup(tmp);
	  free(tmp);
	  tmp = mconcat((*info).content, tokens[*i]);
	  free((*info).content);
	  (*info).content = strdup(tmp);
	  free(tmp);
	}
      (*i)++;
    }
  (*i)--;
  (*info).elem_name = malloc(sizeof(char) * 2);
  (*info).elem_name[0] = g_text;
  (*info).elem_name[1] = '\0';
  tmp = mconcat((*info).elem_name, "TEXT");
  free((*info).elem_name);
  (*info).elem_name = strdup(tmp);
  free(tmp);
  (*info).value_type = STRING;
  (*info).current_tree_type = ATTRIBUT;
}

/*
** Analyze fragments that aren't tokens
*/
void		XMLstate_non_token_fragment(char **tokens, XMLtree_parser *info, int *i)
{
  if ((*info).last_state == DECLARATIONE)
    getTextData(i, tokens, info);
  if ((*info).last_state == ESNAME || (*info).last_state == TYPETOKENE)
    {
      (*info).current_state = ESNAME;
      (*info).current_tree_type = ELEMENT;
      (*info).elem_name = strdup(tokens[*i]);
    }
  if ((*info).last_state == DECLARATIONB && (*info).seg_name == NULL)
    {
      (*info).current_state = ESNAME;
      (*info).current_tree_type = LIST;
      (*info).seg_name = strdup(tokens[*i]);
    }
  if ((*info).last_state == TYPETOKENB)
    {
      XMLidentify_token_type(tokens[((*info).last_state == TYPETOKENB && *i > 0) ? *i - 1 : *i], info);
      (*info).content = strdup(tokens[*i]);
      (*info).current_state = VALUE;
    }
  if ((*info).last_state == ASSIGNEMENT)
    (*info).current_state = ERROR;
}

/*
** Analyze fragments that are tokens
*/
void		XMLstate_token_fragment(const char *fragment, XMLtree_parser *info)
{
  switch (fragment[0]) {
  case '=':
    (*info).current_state = ASSIGNEMENT;
    break ;
  case '\"':
    if ((*info).last_state == VALUE)
      (*info).current_state = TYPETOKENE;
    if ((*info).last_state == ASSIGNEMENT)
      (*info).current_state = TYPETOKENB;
    if ((*info).last_state != VALUE && (*info).last_state != ASSIGNEMENT)
      (*info).current_state = ERROR;
    break ;
  case '<':
    (*info).current_state = DECLARATIONB;
    break ;
  case '>':
    (*info).current_state = DECLARATIONE;
    break ;
  case '/':
    (*info).current_state = LISTE;
    (*info).current_tree_type = CLOSEGROUP;
    break ;
  default :
    break ;
  }
}

#endif		/* __XML_STATE_PARSER_C__ */
