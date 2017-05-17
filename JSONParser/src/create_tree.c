#include	"JSONParser.h"
#include	<stdio.h>

int		str_is_num(const char *str)
{
  int		i = 0;

  while (str[i] != '\0')
    {
      if (str[i] < '0' && str[i] > '9')
	return (-1);
      i++;
    }
  return (0);
}

int		str_n_is_num(const char *str, int max)
{
  int		i = 0;

  while (str[i] != '\0' && i < max)
    {
      if (str[i] < '0' && str[i] > '9')
	return (-1);
      i++;
    }
  return (0);
}

int		is_a_token(const char *fragment, const char *sep)
{
  int		i = 0;

  while (fragment[i] != '\0')
    {
      if (strcis(sep, fragment[i]) == -1)
	return (-1);
      i++;
    }
  return (0);
}

void		identify_token_type(const char *fragment, tree_parser *info)
{
  int		decimal_pos;

  if (fragment[0] == '\"')
    {
      (*info).value_type = STRING;
      (*info).current_state = VALUE;
      (*info).current_tree_type = ATTRIBUT;
      return ;
    }
  if (strcmp(fragment, "null") == 0)
    {
      (*info).value_type = NULLOBJ;
      (*info).current_state = VALUE;
      (*info).current_tree_type = ATTRIBUT;
      return ;
    }
  if (strcmp(fragment, "true") == 0 || strcmp(fragment, "false") == 0)
    {
      (*info).value_type = BOOL;
      (*info).current_state = VALUE;
      (*info).current_tree_type = ATTRIBUT;
      return ;
    }
  if ((decimal_pos = strcis(fragment, '.')) != -1 && str_n_is_num(fragment, decimal_pos) == 0 \
      && str_is_num(fragment + decimal_pos) == 0)
    {
      (*info).value_type = DECIMAL;
      (*info).current_state = VALUE;
      (*info).current_tree_type = ATTRIBUT;
      return ;
    }
  if (str_is_num(fragment) == 0)
    {
      (*info).value_type = INTEGER;
      (*info).current_state = VALUE;
      (*info).current_tree_type = ATTRIBUT;
      return ;
    }
  (*info).value_type = UNKNOW;
  return ;
}

void		state_token_fragment(const char *fragment, tree_parser *info, message *msg)
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

void		add_segment(tree_parser *info, message **msg)
{
  int		is_a_group;
  int		seg_type;

  seg_type = ((*info).current_tree_type == SEGMENT) ? SSEG : ((*info).current_tree_type == LIST) ? SLIST : STAB;
  is_a_group = ((*info).current_tree_type == SEGMENT) ? 0 : 1;
  newSegment(&((*msg)->segment), (*info).elem_name, getNextID((*msg)->segment),	\
	     is_a_group, (*info).is_in_list + (*info).is_in_tab, (*info).is_in_list + (*info).is_in_tab, \
	     seg_type);
  if ((*info).elem_name != NULL)
    free((*info).elem_name);
  (*info).elem_name = NULL;
  (*info).last_tree_type = (*info).current_tree_type;
  (*info).current_tree_type = NOPE;
  if (seg_type == SLIST)
    (*info).is_in_list++;
  if (seg_type == STAB)
    (*info).is_in_tab++;
}

void		add_chunk_to_tree(tree_parser *info, message **msg)
{
  switch ((*info).current_tree_type)
    {
    case CLOSEGROUP:
      closeGroupSegment(&((*msg)->segment));
      if ((*info).last_state == TABE || ((*msg)->segment != NULL && (*msg)->segment->type == STAB))
      	(*info).is_in_tab--;
      if ((*info).last_state == LISTE ||((*msg)->segment != NULL && (*msg)->segment->type == SLIST))
      	(*info).is_in_list--;
      (*info).last_tree_type = (*info).current_tree_type;
      (*info).current_tree_type = NOPE;
      break;
    case SEGMENT:
      add_segment(info, msg);
      break;
    case LIST:
      add_segment(info, msg);
      break;
    case TAB:
      add_segment(info, msg);
      break;
    case ELEMENT:
      puts("ASKED to add ELEM");
      newElement(&((*msg)->segment->element), (*info).elem_name, getNextID((*msg)->segment));
      if ((*info).elem_name != NULL)
	free((*info).elem_name);
      (*info).last_tree_type = (*info).current_tree_type;
      (*info).current_tree_type = NOPE;
      break;
    case ATTRIBUT:
      if ((*info).content == NULL)
	return ;
      if (newElement(&((*msg)->segment->element), (*info).elem_name,	\
		     getNextID((*msg)->segment)) == 0)
	{
	  (*info).current_state = ERROR;
	  return ;
	}
      newAttribut(&((*msg)->segment->element->attribut), (*info).attr_name, \
		  lastAttributID(((*msg)->segment->element->attribut)) + 1, (*info).content, (*info).value_type);
      if ((*info).attr_name != NULL)
	free((*info).attr_name);
      (*info).attr_name = NULL;
      if ((*info).elem_name != NULL)
	free((*info).elem_name);
      (*info).elem_name = NULL;
      if ((*info).content != NULL)
	free((*info).content);
      (*info).content = NULL;
      (*info).value_type = UNKNOW;
      (*info).current_tree_type = NOPE;
      (*info).last_tree_type = ATTRIBUT;
      break;
    default:
      break;
    }
}

tree_parser	init_tree_parser()
{
  tree_parser	info;

  info.seg_name = NULL;
  info.elem_name = NULL;
  info.attr_name = NULL;
  info.content = NULL;
  info.current_state = NONE;
  info.last_state = NONE;
  info.current_tree_type = NOPE;
  info.last_tree_type = NOPE;
  info.is_in_list = 0;
  info.is_in_tab = 0;
  info.list_in_tab = 0;
  return (info);
}

message		*create_tree(char **tokens)
{
  message	*ret;
  int		i;
  tree_parser	info;
  
  ret = NULL;
  info = init_tree_parser();
  newMessage(&ret, 1);
  i = 0;
  while (tokens[i] != NULL)
    {
      if (info.current_state == ERROR)
	{
	  dprintf(2, "SYNTAX ERROR\tNear : \"%s %s %s\"\nCurrent tree parsed : \n", \
		  tokens[i - 1], tokens[i], tokens[i + 1]);
	  if (ret != NULL)
	    dumpMessage(ret);
	  deleteMessages(&ret);
	  return (NULL);
	}
      if (is_a_token(tokens[i], ",[]{}:\"") == 0)
	state_token_fragment(tokens[i], &info, ret);
      if (is_a_token(tokens[i], ",[]{}:\"") != 0 || (info.current_state == VALUE || \
							  info.current_state == ESNAME))
	{
	  if (info.current_state == ESNAME || info.last_state == DECLARATIONB)
	    info.elem_name = strdup(tokens[i]);
	  if (info.last_state == ASSIGNEMENT || info.last_state == TYPETOKENB || info.current_state == VALUE || \
	      (info.last_state == SEPARATOR && ret->segment->type == STAB))
	    {
	      identify_token_type(tokens[i], &info);
	      info.content = strdup(tokens[i]);
	    }
	}
      if (info.current_tree_type != NOPE)
	add_chunk_to_tree(&info, &ret);
      i++;
      info.last_state = info.current_state;
    }
  return (ret);
}
