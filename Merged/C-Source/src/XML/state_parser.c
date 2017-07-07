#ifndef		__XML_STATE_PARSER_C__
# define	__XML_STATE_PARSER_C__

# include	"XMLParser.h"
# include	<stdio.h>

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
  // last_state = DECLARATIONE means that the last token encountered was (>)
  // Cause there isn't token currently encountered the following content is text data
  if ((*info).last_state == DECLARATIONE)
    getTextData(i, tokens, info);
  // 
  if ((*info).last_state == ESNAME || (*info).last_state == TYPETOKENE)
    {
      (*info).current_state = ESNAME;
      (*info).elem_name = strdup(tokens[*i]);
    }
  // if the last token was DECLARATIONB (<) this means that it's the tag's name
  if ((*info).last_state == DECLARATIONB && (*info).seg_name == NULL)
    {
      (*info).current_state = ESNAME;
      (*info).current_tree_type = LIST;
      (*info).seg_name = strdup(tokens[*i]);
    }
  // If the last token was an opening quote then it's obviously the value. 
  // If content != NULL means that the value has been already haverested.
  if ((*info).content == NULL && (*info).last_state == TYPETOKENB)
    {
      XMLidentify_token_type(tokens[((*info).last_state == TYPETOKENB && *i > 0) ? *i - 1 : *i], info);
      (*info).content = strdup(tokens[*i]);
      (*info).current_state = VALUE;
    }
  // If the last token encountered was ASSIGNEMENT (=) and there's no token right after, it's an error.
  // <example attr=value/> <--- this is wrong
  // <example attr="value"/> <--- this is correct
  if ((*info).last_state == ASSIGNEMENT && is_a_token(tokens[*i], "<>/\"=\'") != 0)
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
    // If last_state = TYPETOKENB (opening quote) and the current one is another quote 
    // this means that the encountered quote is the closing one
    if ((*info).last_state == TYPETOKENB)
      {
	(*info).current_state = TYPETOKENE;
	(*info).current_tree_type = ATTRIBUT;
	(*info).content = strdup("");
	(*info).value_type = STRING;
      }
    // If last_state = VALUE means that the current token (") is a closing quote
    if ((*info).last_state == VALUE)
      {
	(*info).current_state = TYPETOKENE;
	(*info).current_tree_type = ATTRIBUT;
      }
    // If last_state = ASSIGNEMENT (=) means that the current token (") is an opening quote
    if ((*info).last_state == ASSIGNEMENT)
      (*info).current_state = TYPETOKENB;
    // If last_state doesn't match the previous if it's an error.
    if ((*info).last_state != VALUE && (*info).last_state != ASSIGNEMENT && (*info).last_state != TYPETOKENB)
      (*info).current_state = ERROR;
    break ;
  case '<':
    (*info).current_state = DECLARATIONB;
    break ;
  case '>':
    (*info).current_state = DECLARATIONE;
    break ;
  case '/':
    // If the current token encountered is (/) it means that a tag is closed
    (*info).current_state = LISTE;
    (*info).current_tree_type = CLOSEGROUP;
    break ;
  default :
    // Will never go there.
    break ;
  }
}

#endif		/* __XML_STATE_PARSER_C__ */
