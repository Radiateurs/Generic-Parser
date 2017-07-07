#ifndef		__JSON_STATE_PARSER_C__
# define	__JSON_STATE_PARSER_C__

# include	"JSONParser.h"

void		JSONstate_non_token_fragment(char **tokens, JSONtree_parser *info, int *i, message *msg)
{
  if ((*info).current_state == ESNAME || (*info).last_state == DECLARATIONB)
    (*info).elem_name = strdup(tokens[*i]);
  if ((*info).last_state == ASSIGNEMENT || (*info).last_state == TYPETOKENB || (*info).current_state == VALUE || \
      ((*info).last_state == SEPARATOR && msg->segment->type == STAB))
    {
      JSONidentify_token_type(tokens[((*info).last_state == TYPETOKENB) ? *i + 1 : *i], info);
      (*info).content = strdup(tokens[*i]);
    }
}

void		JSONstate_token_fragment(const char *fragment, JSONtree_parser *info, message *msg)
{
  if ((*info).last_state == DECLARATIONB && fragment[0] != '\"')
    {
      (*info).current_state = ESNAME;
      return ;
    }
  if ((*info).last_state == TYPETOKENB && fragment[0] != '\"')
    {
      (*info).current_state = VALUE;
      return ;
    }
  switch (fragment[0]) {
  case ':':
    (*info).current_state = ASSIGNEMENT;
    break ;
  case '\"':
    if ((*info).last_state == DECLARATIONB)
      {
	if ((*info).elem_name == NULL)
	  (*info).elem_name = strdup("");
	(*info).current_state = DECLARATIONE;
      }
    if ((*info).last_state == TYPETOKENB)
      {
	if ((*info).content == NULL)
	  (*info).content = strdup("");
	(*info).current_state = TYPETOKENE;
	(*info).current_tree_type = ATTRIBUT;
	(*info).value_type = STRING;
      }
    if ((*info).last_state == ESNAME)
      (*info).current_state = DECLARATIONE;
    if ((*info).last_state == LISTB || (*info).last_state == LISTE)
      (*info).current_state = DECLARATIONB;
    if ((*info).last_state == SEPARATOR)
      {
	if (msg->segment != NULL && msg->segment->type == STAB)
	  (*info).current_state = TYPETOKENB;
	else
	  (*info).current_state = DECLARATIONB;
      }
    if ((*info).last_state == ASSIGNEMENT || (*info).last_state == TABB)
      (*info).current_state = TYPETOKENB;
    if ((*info).last_state == VALUE)
      (*info).current_state = TYPETOKENE;
    break ;
  case '[':
    if ((*info).last_state == ASSIGNEMENT || (*info).last_state == TABB || (*info).last_state == NONE || \
	((*info).last_state == SEPARATOR && msg->segment != NULL && msg->segment->type == STAB))
      {
	(*info).current_state = TABB;
	(*info).current_tree_type = TAB;
      }
    else
      (*info).current_state = ERROR;
    break ;
  case ']':
    if ((*info).last_state == ASSIGNEMENT)
      (*info).current_state = ERROR;
    (*info).current_state = TABE;
    (*info).current_tree_type = CLOSEGROUP;
    break ;
  case '{':
    if ((*info).last_state == TABB || ((*info).last_state == SEPARATOR && (*info).is_in_tab != 0) || \
	(*info).last_state == NONE || (*info).last_state == ASSIGNEMENT || (*info).last_state == SEPARATOR)
      {
	(*info).current_state = LISTB;
	(*info).current_tree_type = LIST;
      }
    else
      (*info).current_state = ERROR;
    break ;
  case '}':
    if ((*info).last_state == ASSIGNEMENT)
      (*info).current_state = ERROR;
    if ((*info).last_state == VALUE || (*info).last_state == TABE ||	\
	(*info).last_state == LISTE || (*info).last_state == TYPETOKENE || \
	(*info).last_state == LISTB)
      {
	(*info).current_state = LISTE;
	(*info).current_tree_type = CLOSEGROUP;
      }
    break ;
  case ',':
    if ((*info).last_state == ASSIGNEMENT)
      (*info).current_state = ERROR;
    if ((*info).last_state == VALUE || (*info).last_state == TYPETOKENE || (*info).last_state == TABE || \
	(*info).last_state == LISTE ||(*info).last_state == SEPARATOR)
      (*info).current_state = SEPARATOR;
    else
      (*info).current_state = ERROR;
    if ((*info).last_state == SEPARATOR)
      (*info).current_tree_type = ELEMENT;
    break ;
  }
}

#endif		/* __JSON_STATE_PARSER_C__ */
