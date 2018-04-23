

#include "Swr_Model.h"

using namespace Common;

/*-------------------------------------------------------------------------------\
|                             Swr_Model											 |
\-------------------------------------------------------------------------------*/
Swr_Model::Swr_Model()
{
	//section 0 - SWR_MODELHeader : black/grey
	listTagColors.push_back(std::vector<std::vector<string>>());
	listTagColors.back().push_back(std::vector<string>());
	listTagColors.back().back().push_back("#232323");			//background color
	listTagColors.back().back().push_back("#FFFFFF");			//font color (just to possibility read from background color)
	listTagColors.back().push_back(std::vector<string>());
	listTagColors.back().back().push_back("#464646");			//bg
	listTagColors.back().back().push_back("#FFFFFF");			//f

	//section 1 - SWR_MODELUnk0AEntry : red
	listTagColors.push_back(std::vector<std::vector<string>>());
	listTagColors.back().push_back(std::vector<string>());
	listTagColors.back().back().push_back("#CC0000");			//bg
	listTagColors.back().back().push_back("#FFFFFF");			//f
	listTagColors.back().push_back(std::vector<string>());
	listTagColors.back().back().push_back("#CC7777");			//bg
	listTagColors.back().back().push_back("#FFFFFF");			//f

	//section 2 - SWR_MODELUnk0BEntry : green
	listTagColors.push_back(std::vector<std::vector<string>>());
	listTagColors.back().push_back(std::vector<string>());
	listTagColors.back().back().push_back("#00CC00");			//bg
	listTagColors.back().back().push_back("#FFFFFF");			//f
	listTagColors.back().push_back(std::vector<string>());
	listTagColors.back().back().push_back("#77CC77");			//bg
	listTagColors.back().back().push_back("#FFFFFF");			//f

	//section 3 - SWR_MODELUnk1Entry : bleu
	listTagColors.push_back(std::vector<std::vector<string>>());
	listTagColors.back().push_back(std::vector<string>());
	listTagColors.back().back().push_back("#0000CC");			//bg
	listTagColors.back().back().push_back("#FFFFFF");			//f
	listTagColors.back().push_back(std::vector<string>());
	listTagColors.back().back().push_back("#7777CC");			//bg
	listTagColors.back().back().push_back("#FFFFFF");			//f




	//section 5 - SWR_MODELUnk2Entry : yellow
	listTagColors.push_back(std::vector<std::vector<string>>());
	listTagColors.back().push_back(std::vector<string>());
	listTagColors.back().back().push_back("#CCCC00");			//bg
	listTagColors.back().back().push_back("#FFFFFF");			//f
	listTagColors.back().push_back(std::vector<string>());
	listTagColors.back().back().push_back("#CCCC77");			//bg
	listTagColors.back().back().push_back("#FFFFFF");			//f


	//section 6 - SWR_MODELUnk3Entry : 
	listTagColors.push_back(std::vector<std::vector<string>>());
	listTagColors.back().push_back(std::vector<string>());
	listTagColors.back().back().push_back("#00CCCC");			//bg
	listTagColors.back().back().push_back("#FFFFFF");			//f
	listTagColors.back().push_back(std::vector<string>());
	listTagColors.back().back().push_back("#77CCCC");			//bg
	listTagColors.back().back().push_back("#FFFFFF");			//f

	//section 7 - SWR_MODELUnk3Entry indexes : 
	listTagColors.push_back(std::vector<std::vector<string>>());
	listTagColors.back().push_back(std::vector<string>());
	listTagColors.back().back().push_back("#009999");			//bg
	listTagColors.back().back().push_back("#FFFFFF");			//f
	listTagColors.back().push_back(std::vector<string>());
	listTagColors.back().back().push_back("#339999");			//bg
	listTagColors.back().back().push_back("#FFFFFF");			//f


	//section 8 - SWR_MODELUnk4Entry : 
	listTagColors.push_back(std::vector<std::vector<string>>());
	listTagColors.back().push_back(std::vector<string>());
	listTagColors.back().back().push_back("#CC00CC");			//bg
	listTagColors.back().back().push_back("#FFFFFF");			//f
	listTagColors.back().push_back(std::vector<string>());
	listTagColors.back().back().push_back("#CC77CC");			//bg
	listTagColors.back().back().push_back("#FFFFFF");			//f


	//section 9 - SWR_MODELUnk4Entry_Next : 
	listTagColors.push_back(std::vector<std::vector<string>>());
	listTagColors.back().push_back(std::vector<string>());
	listTagColors.back().back().push_back("#990099");			//bg
	listTagColors.back().back().push_back("#FFFFFF");			//f
	listTagColors.back().push_back(std::vector<string>());
	listTagColors.back().back().push_back("#993399");			//bg
	listTagColors.back().back().push_back("#FFFFFF");			//f



	//section 10 - SWR_MODELUnk4Entry_Next_b : 
	listTagColors.push_back(std::vector<std::vector<string>>());
	listTagColors.back().push_back(std::vector<string>());
	listTagColors.back().back().push_back("#9900CC");			//bg
	listTagColors.back().back().push_back("#FFFFFF");			//f
	listTagColors.back().push_back(std::vector<string>());
	listTagColors.back().back().push_back("#9933CC");			//bg
	listTagColors.back().back().push_back("#FFFFFF");			//f

	//section 11 - SWR_MODELUnk4Entry_Next_c : 
	listTagColors.push_back(std::vector<std::vector<string>>());
	listTagColors.back().push_back(std::vector<string>());
	listTagColors.back().back().push_back("#CC0099");			//bg
	listTagColors.back().back().push_back("#FFFFFF");			//f
	listTagColors.back().push_back(std::vector<string>());
	listTagColors.back().back().push_back("#CC3399");			//bg
	listTagColors.back().back().push_back("#FFFFFF");			//f

	//section 12 - SWR_MODELUnk4Entry_Next_d : 
	listTagColors.push_back(std::vector<std::vector<string>>());
	listTagColors.back().push_back(std::vector<string>());
	listTagColors.back().back().push_back("#9900AA");			//bg
	listTagColors.back().back().push_back("#FFFFFF");			//f
	listTagColors.back().push_back(std::vector<string>());
	listTagColors.back().back().push_back("#9933AA");			//bg
	listTagColors.back().back().push_back("#FFFFFF");			//f

	//section 13 - SWR_MODELUnk4Entry_Next_e : 
	listTagColors.push_back(std::vector<std::vector<string>>());
	listTagColors.back().push_back(std::vector<string>());
	listTagColors.back().back().push_back("#AA0099");			//bg
	listTagColors.back().back().push_back("#FFFFFF");			//f
	listTagColors.back().push_back(std::vector<string>());
	listTagColors.back().back().push_back("#AA3399");			//bg
	listTagColors.back().back().push_back("#FFFFFF");			//f



	//section 14 - SWR_MODELUnk4Entry_Next2 : 
	listTagColors.push_back(std::vector<std::vector<string>>());
	listTagColors.back().push_back(std::vector<string>());
	listTagColors.back().back().push_back("#770077");			//bg
	listTagColors.back().back().push_back("#FFFFFF");			//f
	listTagColors.back().push_back(std::vector<string>());
	listTagColors.back().back().push_back("#773377");			//bg
	listTagColors.back().back().push_back("#FFFFFF");			//f

	//section 15 - SWR_MODELUnk4Entry_Next2_b : 
	listTagColors.push_back(std::vector<std::vector<string>>());
	listTagColors.back().push_back(std::vector<string>());
	listTagColors.back().back().push_back("#550055");			//bg
	listTagColors.back().back().push_back("#FFFFFF");			//f
	listTagColors.back().push_back(std::vector<string>());
	listTagColors.back().back().push_back("#553355");			//bg
	listTagColors.back().back().push_back("#FFFFFF");			//f





	//section 16 - SWR_MODELUnk4Entry_Next2 : 
	listTagColors.push_back(std::vector<std::vector<string>>());
	listTagColors.back().push_back(std::vector<string>());
	listTagColors.back().back().push_back("#AA00FF");			//bg
	listTagColors.back().back().push_back("#FFFFFF");			//f
	listTagColors.back().push_back(std::vector<string>());
	listTagColors.back().back().push_back("#AA33FF");			//bg
	listTagColors.back().back().push_back("#FFFFFF");			//f

	//section 17 - SWR_MODELUnk4Entry_Next2_b : 
	listTagColors.push_back(std::vector<std::vector<string>>());
	listTagColors.back().push_back(std::vector<string>());
	listTagColors.back().back().push_back("#9900FF");			//bg
	listTagColors.back().back().push_back("#FFFFFF");			//f
	listTagColors.back().push_back(std::vector<string>());
	listTagColors.back().back().push_back("#9933FF");			//bg
	listTagColors.back().back().push_back("#FFFFFF");			//f

	//section 18 - SWR_MODELUnk4Entry_Next2 : 
	listTagColors.push_back(std::vector<std::vector<string>>());
	listTagColors.back().push_back(std::vector<string>());
	listTagColors.back().back().push_back("#7700FF");			//bg
	listTagColors.back().back().push_back("#FFFFFF");			//f
	listTagColors.back().push_back(std::vector<string>());
	listTagColors.back().back().push_back("#7733FF");			//bg
	listTagColors.back().back().push_back("#FFFFFF");			//f

	//section 19 - SWR_MODELUnk4Entry_Next2_b : 
	listTagColors.push_back(std::vector<std::vector<string>>());
	listTagColors.back().push_back(std::vector<string>());
	listTagColors.back().back().push_back("#5500FF");			//bg
	listTagColors.back().back().push_back("#FFFFFF");			//f
	listTagColors.back().push_back(std::vector<string>());
	listTagColors.back().back().push_back("#5533FF");			//bg
	listTagColors.back().back().push_back("#FFFFFF");			//f




	//section 20 - SWR_MODELUnk5Entry : 
	listTagColors.push_back(std::vector<std::vector<string>>());
	listTagColors.back().push_back(std::vector<string>());
	listTagColors.back().back().push_back("#CCCCCC");			//bg
	listTagColors.back().back().push_back("#000000");			//f
	listTagColors.back().push_back(std::vector<string>());
	listTagColors.back().back().push_back("#AAAAAA");			//bg
	listTagColors.back().back().push_back("#000000");			//f


	//section 21 - SWR_MODELUnk5Entry_Box : 
	listTagColors.push_back(std::vector<std::vector<string>>());
	listTagColors.back().push_back(std::vector<string>());
	listTagColors.back().back().push_back("#999999");			//bg
	listTagColors.back().back().push_back("#000000");			//f
	listTagColors.back().push_back(std::vector<string>());
	listTagColors.back().back().push_back("#777777");			//bg
	listTagColors.back().back().push_back("#000000");			//f
}
/*-------------------------------------------------------------------------------\
|                             Reset					                             |
\-------------------------------------------------------------------------------*/
void Swr_Model::Reset()
{
	/*
	mListPart.clear();

	size_t nbText = mListTextureUnit.size();
	for (size_t i = 0; i < nbText; i++)
		delete mListTextureUnit.at(i);
	mListTextureUnit.clear();
	*/
}




/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////









/////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// Xml First Version for Debug ///////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////



/*-------------------------------------------------------------------------------\
|                             save_Xml				                             |
\-------------------------------------------------------------------------------*/
void Swr_Model::save_Xml(string filename, bool show_error)
{
	uint8_t *buf;
	size_t size;

	buf = ReadFile(filename, &size, show_error);
	if (!buf)
		return;

	TiXmlDocument *doc = new TiXmlDocument();
	TiXmlDeclaration* decl = new TiXmlDeclaration("1.0", "UTF-8", "");
	doc->LinkEndChild(decl);

	TiXmlElement* root = new TiXmlElement("Swr_Model");
	EMO_BaseFile::WriteParamString(root, "path", filename);
	
	write_Xml(root, buf, size);

	doc->LinkEndChild(root);



	delete[] buf;

	doc->SaveFile(filename + ".xml");

	return;
}


/*-------------------------------------------------------------------------------\
|                             write_Xml						                     |
\-------------------------------------------------------------------------------*/
void Swr_Model::write_Xml(TiXmlElement *parent, const uint8_t *buf, size_t size)
{
	big_endian = true;
	
	size_t offset = 0;
	size_t nbModels = val32(*(uint32_t*)buf);
	offset += sizeof(uint32_t);


	TiXmlElement* node;
	TiXmlElement* node_models = new TiXmlElement("Models");
	parent->LinkEndChild(node_models);

  size_t i = 0;
  nbModels = 1;
	
	size_t startoffsetModelHeader = offset;
	for (; i < nbModels; i++)
	{
		offset = startoffsetModelHeader + i * sizeof(SWR_MODELHeader);

		SWR_MODELHeader_Used* hdr = (SWR_MODELHeader_Used*)(buf + offset);
		hdr->offset_Section1 = val32(hdr->offset_Section1);
		hdr->offset_Section2 = val32(hdr->offset_Section2);
		size_t offset_NextHeader_Section1 = val32(hdr->offset_NextHeader_Section1);
		offset += sizeof(SWR_MODELHeader);


		TiXmlElement* node_model = new TiXmlElement("Model");
		node_models->LinkEndChild(node_model);





		//Section1 		
		std::vector<uint32_t> dataSection1;
		uint32_t* section1 = (uint32_t*)GetOffsetPtr(buf, hdr->offset_Section1, true);
		offset = hdr->offset_Section1;
		
		TiXmlElement* node_listSection1 = new TiXmlElement("ListSection1");
		node_model->LinkEndChild(node_listSection1);

		size_t nbSection1Elements = (hdr->offset_Section2 - hdr->offset_Section1) / sizeof(uint32_t);
		for (size_t j = 0; j < nbSection1Elements; j++)
		{
			dataSection1.push_back(section1[j]);
			offset += sizeof(uint32_t);

			node = new TiXmlElement("Section1"); node->SetAttribute("flags", UnsignedToString(val32(section1[j]), true)); node_listSection1->LinkEndChild(node);
		}

		
		//Section2
		SWR_MODEL_Section2_Header* hdr_section2 = (SWR_MODEL_Section2_Header*)GetOffsetPtr(buf, hdr->offset_Section2, true);
		offset = hdr->offset_Section2;
		offset += sizeof(SWR_MODEL_Section2_Header);
		size_t sizeSection2 = offset_NextHeader_Section1 - hdr->offset_Section2;
		
		if (memcmp(hdr_section2->signature, SWR_MODEL_SIGNATURE_COMPRESSED, 4) == 0)		//Todo after : take care of "Comp" Compressed
		{
			::printf("Warning: Comp (for Compressed data) is not take care. did you use data from Pc version ? skipped.\n");
			notifyWarning();
			continue;
		}


		//todo take care of Comp

		//Todo Take care of Material/textures informations instead just pass :
		/*
		// Loop over each mesh [material?] (?)
		for (int32_t i = 0; i < nbUint32; i++)
		{
		// Check if this mesh is textured
		if ((1 << (31 - (i & 0x1F))) & data_ModelA[i >> 5])
		{
		data_ModelB_uint32[i] = swap32(data_ModelB_uint32[i]);

		if ((data_ModelB_uint32[i] & 0xFF000000) == 0x0A000000)
		{
		// Load texture
		setTextureHelper(nbUint32, data_ModelB_uint32[i] & 0x00FFFFFF, (char**)&data_ModelB_uint32[i], (int*)&data_ModelB_uint32[i + 1]);

		}else if (data_ModelB_uint32[i] != 0x00000000) {
		// Texture is already in memory, so point into an existing buffer ???
		data_ModelB_uint32[i] = (unsigned int)data_ModelB + data_ModelB_uint32[i];					// a utin32 informations from a size it become a endOffset adress.
		}}}
		*/


		if ((memcmp(hdr_section2->signature, SWR_MODEL_SIGNATURE_MODEL, 4) != 0) &&
			(memcmp(hdr_section2->signature, SWR_MODEL_SIGNATURE_TRACK, 4) != 0) &&
			(memcmp(hdr_section2->signature, SWR_MODEL_SIGNATURE_POD, 4) != 0) &&
			(memcmp(hdr_section2->signature, SWR_MODEL_SIGNATURE_PART, 4) != 0) &&
			(memcmp(hdr_section2->signature, SWR_MODEL_SIGNATURE_SCENE, 4) != 0) &&
			(memcmp(hdr_section2->signature, SWR_MODEL_SIGNATURE_MAlt, 4) != 0) &&
			(memcmp(hdr_section2->signature, SWR_MODEL_SIGNATURE_Pupp, 4) != 0)
			)
		{
			::printf("Warning: Unknowed Section2_header Signature :%c%c%c%c skipped.\n", hdr_section2->signature[0], hdr_section2->signature[1], hdr_section2->signature[2], hdr_section2->signature[3]);
			notifyWarning();
			continue;
		}


		

		if (memcmp(hdr_section2->signature, SWR_MODEL_SIGNATURE_MODEL, 4) == 0)
			node_model->SetAttribute("Type", "Model");
		else if (memcmp(hdr_section2->signature, SWR_MODEL_SIGNATURE_TRACK, 4) == 0)
			node_model->SetAttribute("Type", "Track");
		else if (memcmp(hdr_section2->signature, SWR_MODEL_SIGNATURE_POD, 4) == 0)
			node_model->SetAttribute("Type", "Pod");
		else if (memcmp(hdr_section2->signature, SWR_MODEL_SIGNATURE_PART, 4) == 0)
			node_model->SetAttribute("Type", "Part");
		else if (memcmp(hdr_section2->signature, SWR_MODEL_SIGNATURE_SCENE, 4) == 0)
			node_model->SetAttribute("Type", "Scene");
		else if (memcmp(hdr_section2->signature, SWR_MODEL_SIGNATURE_MAlt, 4) == 0)
			node_model->SetAttribute("Type", "Malt");
		else if (memcmp(hdr_section2->signature, SWR_MODEL_SIGNATURE_Pupp, 4) == 0)
			node_model->SetAttribute("Type", "Pupp");
		


		std::vector<size_t> listPointer_AltN;
		std::vector<size_t> listPointer_Anim;

		TiXmlElement* node_listRefMalt_1 = new TiXmlElement("ListRefMalt_1");
		node_model->LinkEndChild(node_listRefMalt_1);

		uint32_t* section2_unknowParts = (uint32_t*)GetOffsetPtr(buf, offset, true);
		while (*section2_unknowParts != 0xFFFFFFFF)
		{
			if ((*section2_unknowParts != 0) && (val32(*section2_unknowParts) < sizeSection2) && (!checkDuplication(val32(*section2_unknowParts) + hdr->offset_Section2, listPointer_AltN)))
			{
				listPointer_AltN.push_back(val32(*section2_unknowParts) + hdr->offset_Section2);
				
				node = new TiXmlElement("Ref"); node->SetAttribute("offset", UnsignedToString(val32(*section2_unknowParts) + hdr->offset_Section2, true)); node_listRefMalt_1->LinkEndChild(node);
			}

			offset += sizeof(uint32_t);
			section2_unknowParts++;
		}
		offset += sizeof(uint32_t);

		


		bool endFound = false;
		while (!endFound)
		{

			SWR_MODEL_Section2_Header* hdr_section2_sub = (SWR_MODEL_Section2_Header*)GetOffsetPtr(buf, offset, true);
			offset += sizeof(SWR_MODEL_Section2_Header);

			if ((memcmp(hdr_section2_sub->signature, SWR_MODEL_SIGNATURE_ALTN, 4) != 0) &&
				(memcmp(hdr_section2_sub->signature, SWR_MODEL_SIGNATURE_DATA, 4) != 0) &&
				(memcmp(hdr_section2_sub->signature, SWR_MODEL_SIGNATURE_ANIM, 4) != 0) &&
				(memcmp(hdr_section2_sub->signature, SWR_MODEL_SIGNATURE_HEND, 4) != 0)
				)
			{
				::printf("Warning: Unknowed Section2_SubHeader Signature :%c%c%c%c skipped.\n", hdr_section2_sub->signature[0], hdr_section2_sub->signature[1], hdr_section2_sub->signature[2], hdr_section2_sub->signature[3]);
				notifyWarning();
				break;

			}else if (memcmp(hdr_section2_sub->signature, SWR_MODEL_SIGNATURE_ANIM, 4) == 0) {


				size_t startoffset_Anim = offset;
				uint32_t* listOffsetAnim = (uint32_t*)GetOffsetPtr(buf, startoffset_Anim, true);

				size_t inc_Anim = 0;
				while (listOffsetAnim[inc_Anim] != 0)
				{
					listOffsetAnim[inc_Anim] = val32(listOffsetAnim[inc_Anim]);

					if (!checkDuplication(listOffsetAnim[inc_Anim] + hdr->offset_Section2, listPointer_Anim))
						listPointer_Anim.push_back(listOffsetAnim[inc_Anim] + hdr->offset_Section2);

					offset += sizeof(uint32_t);
					inc_Anim++;

					if (listOffsetAnim[inc_Anim] == 0)
						break;
				}
				offset += sizeof(uint32_t);



			}else if (memcmp(hdr_section2_sub->signature, SWR_MODEL_SIGNATURE_DATA, 4) == 0) {

				size_t startoffset_Data = offset;

				size_t nbDatas = val32(*(uint32_t*)GetOffsetPtr(buf, startoffset_Data, true));
				offset += sizeof(uint32_t);

				SWR_Data* datas = (SWR_Data*)GetOffsetPtr(buf, offset, true);

				TiXmlElement* node_data = new TiXmlElement("Datas");
				node_model->LinkEndChild(node_data);

				for (size_t j = 0; j < nbDatas; j++)
				{
					TiXmlElement* node = new TiXmlElement("Data"); node->SetAttribute("unk0", UnsignedToString(datas[j].unk0, true)); node->SetAttribute("unk1", UnsignedToString(datas[j].unk1, true)); node->SetAttribute("unk2", UnsignedToString(datas[j].unk2, true)); node->SetAttribute("unk3", UnsignedToString(datas[j].unk3, true)); node_data->LinkEndChild(node);
					offset += 4 * sizeof(uint8_t);
				}

				//todo understand data is for what ? linked to another files ?

			}else if (memcmp(hdr_section2_sub->signature, SWR_MODEL_SIGNATURE_ALTN, 4) == 0) {


				TiXmlElement* node_listRefMalt_2 = new TiXmlElement("ListRefMalt_2");
				node_model->LinkEndChild(node_listRefMalt_2);


				size_t startoffset_AltN = offset;
				uint32_t* listOffsetAltN = (uint32_t*)GetOffsetPtr(buf, startoffset_AltN, true);

				size_t inc_AltN = 0;
				while (listOffsetAltN[inc_AltN] != 0)
				{
					listOffsetAltN[inc_AltN] = val32(listOffsetAltN[inc_AltN]);

					if (!checkDuplication(listOffsetAltN[inc_AltN] + hdr->offset_Section2, listPointer_AltN))
					{
						listPointer_AltN.push_back(listOffsetAltN[inc_AltN] + hdr->offset_Section2);

						node = new TiXmlElement("Ref"); node->SetAttribute("offset", UnsignedToString(listOffsetAltN[inc_AltN] + hdr->offset_Section2, true)); node_listRefMalt_2->LinkEndChild(node);
					}

					offset += sizeof(uint32_t);
					inc_AltN++;

					if (listOffsetAltN[inc_AltN] == 0)
						break;
				}
				offset += sizeof(uint32_t);

			}else {		// else "Hend" => normal exit.
				endFound = true;
			}
		}



		
		//saddely , it's could have a Malt just after Hend, never referenced (cf Model_115), So we test to add it.
		// hope the filter on first flags could avoid trouble.
		if (!checkDuplication(offset, listPointer_AltN))
			listPointer_AltN.push_back(offset);






		//-----------------------  Malt /AltN :


		TiXmlElement* node_listMalt = new TiXmlElement("ListMalt");
		node_model->LinkEndChild(node_listMalt);			//test Anima Todo unComment


		size_t nbAltN = listPointer_AltN.size();
		for (size_t inc_AltN = 0; inc_AltN< nbAltN; inc_AltN++)
		{
			size_t startSectionAltN = listPointer_AltN.at(inc_AltN);
			offset = startSectionAltN;


			std::vector<size_t> listRecusiveAltN;
			listRecusiveAltN.push_back(offset);

			for (size_t j = 0; j<listRecusiveAltN.size(); j++)
			{
				offset = listRecusiveAltN.at(j);

				if (*(uint32_t*)GetOffsetPtr(buf, offset, true) == 0)
				{
					//write_Coloration_Tag("badPointerComeHere", "uint32_t", " Todo why ?", offset, sizeof(uint32_t), "SWR_AltN_Header", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, j);
					continue;
				}


				TiXmlElement* node_Malt = new TiXmlElement("Malt");
				node_Malt->SetAttribute("startOffset_id", UnsignedToString(offset, true));
				node_listMalt->LinkEndChild(node_Malt);


				
				SWR_AltN_Header* hdr_AltN = (SWR_AltN_Header*)GetOffsetPtr(buf, offset, true);
				hdr_AltN->flags = val32(hdr_AltN->flags);
				hdr_AltN->nb_Childs = val32(hdr_AltN->nb_Childs);
				hdr_AltN->offset_Childs = val32(hdr_AltN->offset_Childs);
				offset += sizeof(SWR_AltN_Header);

				node = new TiXmlElement("flags"); node->SetAttribute("u32", UnsignedToString(hdr_AltN->flags, true)); node_Malt->LinkEndChild(node);
				node = new TiXmlElement("unk0"); node->SetAttribute("u32", UnsignedToString(val32(hdr_AltN->unk0), true)); node_Malt->LinkEndChild(node);
				node = new TiXmlElement("unk1"); node->SetAttribute("u32", UnsignedToString(val32(hdr_AltN->unk1), true)); node_Malt->LinkEndChild(node);
				node = new TiXmlElement("unk2_a"); node->SetAttribute("u8", UnsignedToString(val32(hdr_AltN->unk2_a), true)); node_Malt->LinkEndChild(node);
				node = new TiXmlElement("unk2_b"); node->SetAttribute("u8", UnsignedToString(val32(hdr_AltN->unk2_b), true)); node_Malt->LinkEndChild(node);
				node = new TiXmlElement("unk3"); node->SetAttribute("u16", UnsignedToString(val32(hdr_AltN->unk3), true)); node_Malt->LinkEndChild(node);
				node = new TiXmlElement("unk4"); node->SetAttribute("u32", UnsignedToString(val32(hdr_AltN->unk4), true)); node_Malt->LinkEndChild(node);
				

				//todo: better understand flags to avoid the big switch, if it's possible.

				switch (hdr_AltN->flags)
				{
				case 0x3064:
				{
					SWR_AltN_0x3064* section = (SWR_AltN_0x3064*)GetOffsetPtr(buf, offset, true);
					offset += sizeof(SWR_AltN_0x3064);

					TiXmlElement* node_section = new TiXmlElement("Section_3064");
					node_Malt->LinkEndChild(node_section);
					node = new TiXmlElement("AABB"); 
					node->SetAttribute("minX", FloatToString(val_float(section->minX))); 
					node->SetAttribute("minY", FloatToString(val_float(section->minY)));
					node->SetAttribute("minZ", FloatToString(val_float(section->minZ)));
					node->SetAttribute("maxX", FloatToString(val_float(section->maxX)));
					node->SetAttribute("maxY", FloatToString(val_float(section->maxY)));
					node->SetAttribute("maxZ", FloatToString(val_float(section->maxZ)));
					node_section->LinkEndChild(node);
					node = new TiXmlElement("unk0"); node->SetAttribute("u32", UnsignedToString(val32(section->unk0), true)); node_section->LinkEndChild(node);
					node = new TiXmlElement("unk1"); node->SetAttribute("u32", UnsignedToString(val32(section->unk1), true)); node_section->LinkEndChild(node);

					
					

					size_t startoffset_Section3_listOffset = hdr_AltN->offset_Childs + hdr->offset_Section2;
					offset = startoffset_Section3_listOffset;

					uint32_t* listOffsetAltN_Section3 = (uint32_t*)GetOffsetPtr(buf, offset, true);

					TiXmlElement* node_listSection3 = new TiXmlElement("ListSection3");
					node_section->LinkEndChild(node_listSection3);

					for (size_t k = 0; k < hdr_AltN->nb_Childs; k++)
					{

						size_t startoffset_section3 = val32(listOffsetAltN_Section3[k]) + hdr->offset_Section2;
						offset = startoffset_section3;

						SWR_MODEL_Section3* section3 = (SWR_MODEL_Section3*)GetOffsetPtr(buf, offset, true);
						offset += sizeof(SWR_MODEL_Section3);
						section3->offset_section4 = val32(section3->offset_section4);
						section3->offset_section7 = val32(section3->offset_section7);
						section3->nbElementV90 = val16(section3->nbElementV90);
						section3->typeMode = val16(section3->typeMode);
						section3->nbElementV44 = val16(section3->nbElementV44);
						section3->nbElementV52 = val16(section3->nbElementV52);
						section3->offset_V90 = val32(section3->offset_V90);
						section3->offset_unk40 = val32(section3->offset_unk40);
						section3->offset_unk44 = val32(section3->offset_unk44);
						section3->offset_unk48 = val32(section3->offset_unk48);
						section3->offset_unk52 = val32(section3->offset_unk52);


						TiXmlElement* node_section3 = new TiXmlElement("Section3");
						node_section3->SetAttribute("startOffset", UnsignedToString(startoffset_section3, true));			//debug, todo remove
						node_listSection3->LinkEndChild(node_section3);

						node = new TiXmlElement("AABB");
						node->SetAttribute("minX", FloatToString(val_float(section3->minX)));
						node->SetAttribute("minY", FloatToString(val_float(section3->minY)));
						node->SetAttribute("minZ", FloatToString(val_float(section3->minZ)));
						node->SetAttribute("maxX", FloatToString(val_float(section3->maxX)));
						node->SetAttribute("maxY", FloatToString(val_float(section3->maxY)));
						node->SetAttribute("maxZ", FloatToString(val_float(section3->maxZ)));
						node_section3->LinkEndChild(node);

						node = new TiXmlElement("typeMode"); node->SetAttribute("u16", UnsignedToString(section3->typeMode, true)); node_section3->LinkEndChild(node);
						node = new TiXmlElement("unk60"); node->SetAttribute("u16", UnsignedToString(val16(section3->unk60), true)); node_section3->LinkEndChild(node);
						node = new TiXmlElement("unk62"); node->SetAttribute("u16", UnsignedToString(val16(section3->unk62), true)); node_section3->LinkEndChild(node);


						//todo removes that after debug be sure about While on Section44
						node = new TiXmlElement("nbElementV90"); node->SetAttribute("u16", UnsignedToString(section3->nbElementV90, false)); node_section3->LinkEndChild(node);
						node = new TiXmlElement("nbElementV44"); node->SetAttribute("u16", UnsignedToString(section3->nbElementV44, false)); node_section3->LinkEndChild(node);
						node = new TiXmlElement("nbElementV52"); node->SetAttribute("u16", UnsignedToString(section3->nbElementV52, false)); node_section3->LinkEndChild(node);

						
						
						

						

						if (section3->offset_section4)
						{

							size_t startoffset_section4 = section3->offset_section4 + hdr->offset_Section2;
							offset = startoffset_section4;

							SWR_MODEL_Section4* section4 = (SWR_MODEL_Section4*)GetOffsetPtr(buf, offset, true);
							offset += sizeof(SWR_MODEL_Section4);
							section4->offset_section5 = val32(section4->offset_section5);
							section4->offset_section6 = val32(section4->offset_section6);


							TiXmlElement* node_section4 = new TiXmlElement("Section4");
							node_section3->LinkEndChild(node_section4);

							node = new TiXmlElement("unk0"); node->SetAttribute("u32", UnsignedToString(val32(section4->unk0), true)); node_section4->LinkEndChild(node);
							node = new TiXmlElement("unk4"); node->SetAttribute("u32", UnsignedToString(val32(section4->unk4), true)); node_section4->LinkEndChild(node);
							node = new TiXmlElement("unk6"); node->SetAttribute("u32", UnsignedToString(val32(section4->unk6), true)); node_section4->LinkEndChild(node);






							if (section4->offset_section5)
							{
								size_t startoffset_section5 = section4->offset_section5 + hdr->offset_Section2;
								offset = startoffset_section5;

								SWR_MODEL_Section5* section5 = (SWR_MODEL_Section5*)GetOffsetPtr(buf, offset, true);
								offset += sizeof(SWR_MODEL_Section5);


								TiXmlElement* node_section5 = new TiXmlElement("Section5");
								node_section4->LinkEndChild(node_section5);

								node = new TiXmlElement("unk0"); node->SetAttribute("u32", UnsignedToString(val32(section5->unk0), true)); node_section5->LinkEndChild(node);
								node = new TiXmlElement("unk4"); node->SetAttribute("u16", UnsignedToString(val16(section5->unk4), true)); node_section5->LinkEndChild(node);
								node = new TiXmlElement("unk6"); node->SetAttribute("u16", UnsignedToString(val16(section5->unk6), true)); node_section5->LinkEndChild(node);
								node = new TiXmlElement("unk8_0"); node->SetAttribute("u16", UnsignedToString(val16(section5->unk8[0]), true)); node_section5->LinkEndChild(node);
								node = new TiXmlElement("unk8_1"); node->SetAttribute("u16", UnsignedToString(val16(section5->unk8[1]), true)); node_section5->LinkEndChild(node);
								node = new TiXmlElement("unk12_0"); node->SetAttribute("u8", UnsignedToString(section5->unk12[0], true)); node_section5->LinkEndChild(node);
								node = new TiXmlElement("unk12_1"); node->SetAttribute("u8", UnsignedToString(section5->unk12[1], true)); node_section5->LinkEndChild(node);
								node = new TiXmlElement("unk12_2"); node->SetAttribute("u8", UnsignedToString(section5->unk12[2], true)); node_section5->LinkEndChild(node);
								node = new TiXmlElement("unk12_3"); node->SetAttribute("u8", UnsignedToString(section5->unk12[3], true)); node_section5->LinkEndChild(node);
								node = new TiXmlElement("unk16"); node->SetAttribute("u16", UnsignedToString(val16(section5->unk16), true)); node_section5->LinkEndChild(node);
								node = new TiXmlElement("unk18"); node->SetAttribute("u16", UnsignedToString(val16(section5->unk18), true)); node_section5->LinkEndChild(node);
								node = new TiXmlElement("unk20"); node->SetAttribute("u16", UnsignedToString(val16(section5->unk20), true)); node_section5->LinkEndChild(node);
								node = new TiXmlElement("unk22"); node->SetAttribute("u16", UnsignedToString(val16(section5->unk22), true)); node_section5->LinkEndChild(node);
								node = new TiXmlElement("unk24"); node->SetAttribute("u16", UnsignedToString(val16(section5->unk24), true)); node_section5->LinkEndChild(node);
								node = new TiXmlElement("unk26"); node->SetAttribute("u16", UnsignedToString(val16(section5->unk26), true)); node_section5->LinkEndChild(node);
								node = new TiXmlElement("unk48"); node->SetAttribute("u32", UnsignedToString(val32(section5->unk48), true)); node_section5->LinkEndChild(node);
								node = new TiXmlElement("unk52"); node->SetAttribute("u32", UnsignedToString(val32(section5->unk52), true)); node_section5->LinkEndChild(node);
								node = new TiXmlElement("unk56"); node->SetAttribute("u8", UnsignedToString(section5->unk56, true)); node_section5->LinkEndChild(node);
								node = new TiXmlElement("unk57"); node->SetAttribute("u8", UnsignedToString(section5->unk57, true)); node_section5->LinkEndChild(node);
								node = new TiXmlElement("unk58"); node->SetAttribute("u16", UnsignedToString(val16(section5->unk58), true)); node_section5->LinkEndChild(node);
								node = new TiXmlElement("unk60"); node->SetAttribute("u32", UnsignedToString(val32(section5->unk60), true)); node_section5->LinkEndChild(node);


								for (size_t m = 0; m < 5; m++)
								{
									if (!section5->offset_Section5_b[m])
										continue;

									size_t startoffset_section5_b = val32(section5->offset_Section5_b[m]) + hdr->offset_Section2;
									offset = startoffset_section5_b;

									SWR_MODEL_Section5_b* section5_b = (SWR_MODEL_Section5_b*)GetOffsetPtr(buf, offset, true);

									offset += sizeof(SWR_MODEL_Section5_b);

									TiXmlElement* node_section5b = new TiXmlElement("Section5b");
									node_section5->LinkEndChild(node_section5b);

									node = new TiXmlElement("unk0"); node->SetAttribute("u16", UnsignedToString(val16(section5_b->unk0), true)); node_section5b->LinkEndChild(node);
									node = new TiXmlElement("unk2"); node->SetAttribute("u8", UnsignedToString(section5_b->unk2, true)); node_section5b->LinkEndChild(node);
									node = new TiXmlElement("unk3"); node->SetAttribute("u8", UnsignedToString(section5_b->unk3, true)); node_section5b->LinkEndChild(node);
									node = new TiXmlElement("unk4"); node->SetAttribute("u8", UnsignedToString(section5_b->unk4, true)); node_section5b->LinkEndChild(node);
									node = new TiXmlElement("unk5"); node->SetAttribute("u8", UnsignedToString(section5_b->unk5, true)); node_section5b->LinkEndChild(node);
									node = new TiXmlElement("unk6_a"); node->SetAttribute("u8", UnsignedToString(val16(section5_b->unk6_a), true)); node_section5b->LinkEndChild(node);
									node = new TiXmlElement("unk6_b"); node->SetAttribute("u8", UnsignedToString(val16(section5_b->unk6_b), true)); node_section5b->LinkEndChild(node);
									node = new TiXmlElement("unk8"); node->SetAttribute("u32", UnsignedToString(val32(section5_b->unk8), true)); node_section5b->LinkEndChild(node);
									node = new TiXmlElement("unk12"); node->SetAttribute("u16", UnsignedToString(val16(section5_b->unk12), true)); node_section5b->LinkEndChild(node);
									node = new TiXmlElement("unk14"); node->SetAttribute("u16", UnsignedToString(val16(section5_b->unk14), true)); node_section5b->LinkEndChild(node);
								}

							}


							if (section4->offset_section6)
							{
								size_t startoffset_section6 = section4->offset_section6 + hdr->offset_Section2;
								offset = startoffset_section6;

								SWR_MODEL_Section6* section6 = (SWR_MODEL_Section6*)GetOffsetPtr(buf, offset, true);
								offset += sizeof(SWR_MODEL_Section6);

								TiXmlElement* node_section6 = new TiXmlElement("Section6");
								node_section4->LinkEndChild(node_section6);

								node = new TiXmlElement("unk0"); node->SetAttribute("u32", UnsignedToString(val32(section6->unk0), true)); node_section6->LinkEndChild(node);
								node = new TiXmlElement("unk4"); node->SetAttribute("u16", UnsignedToString(val16(section6->unk4), true)); node_section6->LinkEndChild(node);
								node = new TiXmlElement("unk6_0"); node->SetAttribute("u32", UnsignedToString(val32(section6->unk6[0]), true)); node_section6->LinkEndChild(node);
								node = new TiXmlElement("unk6_1"); node->SetAttribute("u32", UnsignedToString(val32(section6->unk6[1]), true)); node_section6->LinkEndChild(node);
								node = new TiXmlElement("unk14_0"); node->SetAttribute("u32", UnsignedToString(val32(section6->unk14[0]), true)); node_section6->LinkEndChild(node);
								node = new TiXmlElement("unk14_1"); node->SetAttribute("u32", UnsignedToString(val32(section6->unk14[1]), true)); node_section6->LinkEndChild(node);
								node = new TiXmlElement("unk22_0"); node->SetAttribute("u8", UnsignedToString(section6->unk22[0], true)); node_section6->LinkEndChild(node);
								node = new TiXmlElement("unk22_1"); node->SetAttribute("u8", UnsignedToString(section6->unk22[1], true)); node_section6->LinkEndChild(node);
								node = new TiXmlElement("unk24"); node->SetAttribute("u32", UnsignedToString(val32(section6->unk24), true)); node_section6->LinkEndChild(node);
								node = new TiXmlElement("unk28"); node->SetAttribute("u32", UnsignedToString(val32(section6->unk28), true)); node_section6->LinkEndChild(node);
								node = new TiXmlElement("unk32"); node->SetAttribute("u16", UnsignedToString(val16(section6->unk32), true)); node_section6->LinkEndChild(node);
								node = new TiXmlElement("unk34"); node->SetAttribute("u16", UnsignedToString(val16(section6->unk34), true)); node_section6->LinkEndChild(node);
								node = new TiXmlElement("unk36"); node->SetAttribute("u16", UnsignedToString(val16(section6->unk36), true)); node_section6->LinkEndChild(node);
								node = new TiXmlElement("unk38"); node->SetAttribute("u16", UnsignedToString(val16(section6->unk38), true)); node_section6->LinkEndChild(node);
								node = new TiXmlElement("unk40"); node->SetAttribute("u32", UnsignedToString(val32(section6->unk40), true)); node_section6->LinkEndChild(node);
								node = new TiXmlElement("unk44"); node->SetAttribute("u32", UnsignedToString(val32(section6->unk44), true)); node_section6->LinkEndChild(node);
								node = new TiXmlElement("unk48"); node->SetAttribute("u32", UnsignedToString(val32(section6->unk48), true)); node_section6->LinkEndChild(node);
							}

							//reinverse for another time.
							section4->offset_section5 = val32(section4->offset_section5);
							section4->offset_section6 = val32(section4->offset_section6);
						}



						if (section3->offset_section7)
						{
							size_t startoffset_section7 = section3->offset_section7 + hdr->offset_Section2;
							offset = startoffset_section7;

							SWR_MODEL_Section7* section7 = (SWR_MODEL_Section7*)GetOffsetPtr(buf, offset, true);
							offset += sizeof(SWR_MODEL_Section7);

							
							TiXmlElement* node_section7 = new TiXmlElement("Section7");
							node_section3->LinkEndChild(node_section7);

							node = new TiXmlElement("unk0"); node->SetAttribute("u16", UnsignedToString(val16(section7->unk0), true)); node_section7->LinkEndChild(node);
							node = new TiXmlElement("unk2_0"); node->SetAttribute("u8", UnsignedToString(section7->unk2[0], true)); node_section7->LinkEndChild(node);
							node = new TiXmlElement("unk2_1"); node->SetAttribute("u8", UnsignedToString(section7->unk2[1], true)); node_section7->LinkEndChild(node);
							node = new TiXmlElement("unk2_2"); node->SetAttribute("u8", UnsignedToString(section7->unk2[2], true)); node_section7->LinkEndChild(node);
							node = new TiXmlElement("unk2_3"); node->SetAttribute("u8", UnsignedToString(section7->unk2[3], true)); node_section7->LinkEndChild(node);
							node = new TiXmlElement("unk6"); node->SetAttribute("u16", UnsignedToString(val16(section7->unk6), true)); node_section7->LinkEndChild(node);
							node = new TiXmlElement("unk8"); node->SetAttribute("u16", UnsignedToString(val16(section7->unk8), true)); node_section7->LinkEndChild(node);
							node = new TiXmlElement("unk10"); node->SetAttribute("u16", UnsignedToString(val16(section7->unk10), true)); node_section7->LinkEndChild(node);
							node = new TiXmlElement("unk12_0"); node->SetAttribute("u8", UnsignedToString(section7->unk12[0], true)); node_section7->LinkEndChild(node);
							node = new TiXmlElement("unk12_1"); node->SetAttribute("u8", UnsignedToString(section7->unk12[1], true)); node_section7->LinkEndChild(node);
							node = new TiXmlElement("unk12_2"); node->SetAttribute("u8", UnsignedToString(section7->unk12[2], true)); node_section7->LinkEndChild(node);
							node = new TiXmlElement("unk12_3"); node->SetAttribute("u8", UnsignedToString(section7->unk12[3], true)); node_section7->LinkEndChild(node);
							node = new TiXmlElement("unk12_4"); node->SetAttribute("u8", UnsignedToString(section7->unk12[4], true)); node_section7->LinkEndChild(node);
							node = new TiXmlElement("unk12_5"); node->SetAttribute("u8", UnsignedToString(section7->unk12[5], true)); node_section7->LinkEndChild(node);
							node = new TiXmlElement("unk12_6"); node->SetAttribute("u8", UnsignedToString(section7->unk12[6], true)); node_section7->LinkEndChild(node);
							node = new TiXmlElement("unk12_7"); node->SetAttribute("u8", UnsignedToString(section7->unk12[7], true)); node_section7->LinkEndChild(node);
							node = new TiXmlElement("unk20"); node->SetAttribute("float", FloatToString(val_float(section7->unk20))); node_section7->LinkEndChild(node);
							node = new TiXmlElement("unk24"); node->SetAttribute("float", FloatToString(val_float(section7->unk24))); node_section7->LinkEndChild(node);
							node = new TiXmlElement("unk28"); node->SetAttribute("float", FloatToString(val_float(section7->unk28))); node_section7->LinkEndChild(node);
							node = new TiXmlElement("unk32"); node->SetAttribute("float", FloatToString(val_float(section7->unk32))); node_section7->LinkEndChild(node);
							node = new TiXmlElement("unk36"); node->SetAttribute("float", FloatToString(val_float(section7->unk36))); node_section7->LinkEndChild(node);
							node = new TiXmlElement("unk40"); node->SetAttribute("u32", UnsignedToString(val32(section7->unk40), true)); node_section7->LinkEndChild(node);
							node = new TiXmlElement("unk44"); node->SetAttribute("u32", UnsignedToString(val32(section7->unk44), true)); node_section7->LinkEndChild(node);
							node = new TiXmlElement("unk48"); node->SetAttribute("u16", UnsignedToString(val16(section7->unk48), true)); node_section7->LinkEndChild(node);
							node = new TiXmlElement("unk50"); node->SetAttribute("u16", UnsignedToString(val16(section7->unk50), true)); node_section7->LinkEndChild(node);
							node = new TiXmlElement("unk52"); node->SetAttribute("u32", UnsignedToString(val32(section7->unk52), true)); node_section7->LinkEndChild(node);
							node = new TiXmlElement("unk56"); node->SetAttribute("u32", UnsignedToString(val32(section7->unk56), true)); node_section7->LinkEndChild(node);


							if ((val32(section7->unk52) & 0xFFFF) == 0x6C3C)			//todo test if it's work on all files.
							{
								size_t startoffset_section7b = offset;

								SWR_MODEL_Section7_b* section7_b = (SWR_MODEL_Section7_b*)GetOffsetPtr(buf, offset, true);
								offset += sizeof(SWR_MODEL_Section7_b);

								TiXmlElement* node_section7b = new TiXmlElement("Section7b");
								node_section7->LinkEndChild(node_section7b);

								node = new TiXmlElement("unk0"); node->SetAttribute("u32", UnsignedToString(val32(section7_b->unk0), true)); node_section7b->LinkEndChild(node);
								node = new TiXmlElement("unk1"); node->SetAttribute("u32", UnsignedToString(val32(section7_b->unk1), true)); node_section7b->LinkEndChild(node);
								node = new TiXmlElement("unk2"); node->SetAttribute("u32", UnsignedToString(val32(section7_b->unk2), true)); node_section7b->LinkEndChild(node);
							}


							TiXmlElement* node_Listsection8 = new TiXmlElement("ListSection8");
							node_section7->LinkEndChild(node_Listsection8);

							std::vector<size_t> listOffsetSection8;
							listOffsetSection8.push_back(val32(section7->offset_section8));

							for (size_t m = 0; m < listOffsetSection8.size(); m++)
							{
								if (!listOffsetSection8.at(m))
									continue;

								size_t startoffset_section8 = listOffsetSection8.at(m) + hdr->offset_Section2;
								offset = startoffset_section8;

								SWR_MODEL_Section8* section8 = (SWR_MODEL_Section8*)GetOffsetPtr(buf, offset, true);
								
								TiXmlElement* node_section8 = new TiXmlElement("Section8");
								node_section8->SetAttribute("startOffset", UnsignedToString(offset, true));
								node_Listsection8->LinkEndChild(node_section8);

								offset += sizeof(SWR_MODEL_Section8);

								node = new TiXmlElement("unk0_0"); node->SetAttribute("float", FloatToString(val_float(section8->unk0[0]))); node_section8->LinkEndChild(node);
								node = new TiXmlElement("unk0_1"); node->SetAttribute("float", FloatToString(val_float(section8->unk0[1]))); node_section8->LinkEndChild(node);
								node = new TiXmlElement("unk0_2"); node->SetAttribute("float", FloatToString(val_float(section8->unk0[2]))); node_section8->LinkEndChild(node);
								node = new TiXmlElement("unk12_0"); node->SetAttribute("float", FloatToString(val_float(section8->unk12[0]))); node_section8->LinkEndChild(node);
								node = new TiXmlElement("unk12_1"); node->SetAttribute("float", FloatToString(val_float(section8->unk12[1]))); node_section8->LinkEndChild(node);
								node = new TiXmlElement("unk12_2"); node->SetAttribute("float", FloatToString(val_float(section8->unk12[2]))); node_section8->LinkEndChild(node);
								node = new TiXmlElement("unk24"); node->SetAttribute("float", FloatToString(val_float(section8->unk24))); node_section8->LinkEndChild(node);
								node = new TiXmlElement("unk28"); node->SetAttribute("float", FloatToString(val_float(section8->unk28))); node_section8->LinkEndChild(node);
								node = new TiXmlElement("unk32"); node->SetAttribute("u32", UnsignedToString(val32(section8->unk32), true)); node_section8->LinkEndChild(node);
								node = new TiXmlElement("unk36"); node->SetAttribute("u16", UnsignedToString(val16(section8->unk36), true)); node_section8->LinkEndChild(node);
								node = new TiXmlElement("unk38"); node->SetAttribute("u16", UnsignedToString(val16(section8->unk38), true)); node_section8->LinkEndChild(node);
								node = new TiXmlElement("offset_nextSection8"); node->SetAttribute("u32", UnsignedToString(val32(section8->offset_next_section8), true)); node_section8->LinkEndChild(node);

								listOffsetSection8.push_back(val32(section8->offset_next_section8));
							}
						}


						if (section3->offset_V90)									//it's a list of numberElements for next parts.
						{
							size_t startoffset_sectionV90 = section3->offset_V90 + hdr->offset_Section2;
							offset = startoffset_sectionV90;

							TiXmlElement* node_sectionV90 = new TiXmlElement("SectionV90");
							node_sectionV90->SetAttribute("startOffset", UnsignedToString(startoffset_sectionV90, true));
							node_section3->LinkEndChild(node_sectionV90);

							uint32_t* listValues = (uint32_t*)GetOffsetPtr(buf, offset, true);

							for (size_t m = 0; m < section3->nbElementV90; m++)
							{

                node = new TiXmlElement("Value"); 
                node->SetAttribute("u32", UnsignedToString(listValues[m], true));
                node_sectionV90->LinkEndChild(node);

								offset += sizeof(uint32_t);
							}
						}


#if 0
// Possibly indices
            if (section3->offset_unk40)
						{
							size_t startoffset_section40 = section3->offset_unk40 + hdr->offset_Section2;
							offset = startoffset_section40;

							SWR_MODEL_Section40* section40 = (SWR_MODEL_Section48*)GetOffsetPtr(buf, offset, true);

							TiXmlElement* node_section48 = new TiXmlElement("Section40");
							node_section40->SetAttribute("startOffset", UnsignedToString(startoffset_section40, true));
							node_section3->LinkEndChild(node_section40);

							size_t inc = 0;
							while (section40->unk0 != 0xDF)
							{
								node = new TiXmlElement("Value"); 
								node->SetAttribute("u16", UnsignedToString(section48->unk0, true));
								node_section48->LinkEndChild(node);

								offset += sizeof(SWR_MODEL_Section48);
								section48++;
								inc++;
							}
							offset += 2 * sizeof(uint32_t);

							node_section40->SetAttribute("debugNbElements", inc);
						}
#endif

						//if ((section3->offset_unk40) && (section3->offset_unk44))			//44 is necessary ? => yes, it's 40 witch is not necessary.
						if (section3->offset_unk44)
						{
							size_t startoffset_section44 = section3->offset_unk44 + hdr->offset_Section2;
							offset = startoffset_section44;

							size_t nbElements = 0;
							switch (section3->typeMode)
							{
							case 3: nbElements = 3 * section3->nbElementV44; break;
								//case 4: nbElements = 4 * section3->nbUnk44; break;
							case 4: nbElements = 3 * section3->nbElementV44; break;

							case 5:
							{
								if (section3->offset_V90)
								{
									uint32_t* listValues = (uint32_t*)GetOffsetPtr(buf, section3->offset_V90 + hdr->offset_Section2, true);
									for (size_t m = 0; m < section3->nbElementV90; m++)
									{
										nbElements += 3 * val32(listValues[m]);
									}
								}
							}
							break;

							default:
								break;
							}


							float* values_f = (float*)GetOffsetPtr(buf, offset, true);
							uint16_t* values_u16 = (uint16_t*)GetOffsetPtr(buf, offset, true);
							
							TiXmlElement* node_section44 = new TiXmlElement("Section44");
							node_section44->SetAttribute("startOffset", UnsignedToString(offset, true));
							node_section3->LinkEndChild(node_section44);


							for (size_t m = 0; m < nbElements; m++)
							{
								//todo understand why model 114 and &52 have float, instead of float16.
								//node = new TiXmlElement("Value"); node->SetAttribute("float", FloatToString(val_float(values_f[m]))); node_section44->LinkEndChild(node);
								node = new TiXmlElement("Value"); node->SetAttribute("float16", FloatToString(float16ToFloat(values_u16[m]))); node_section44->LinkEndChild(node);
							}


							offset += nbElements * sizeof(uint16_t);
						}



						if (section3->offset_unk48)
						{
							size_t startoffset_section48 = section3->offset_unk48 + hdr->offset_Section2;
							offset = startoffset_section48;

							SWR_MODEL_Section48* section48 = (SWR_MODEL_Section48*)GetOffsetPtr(buf, offset, true);

							TiXmlElement* node_section48 = new TiXmlElement("Section48");
							node_section48->SetAttribute("startOffset", UnsignedToString(startoffset_section48, true));
							node_section3->LinkEndChild(node_section48);

							size_t inc = 0;
							while (section48->unk0 != 0xDF)
							{
								node = new TiXmlElement("Value"); 
								node->SetAttribute("unk0", UnsignedToString(section48->unk0, true));
								node->SetAttribute("unk1", UnsignedToString(section48->unk1, true));
								node->SetAttribute("unk2", UnsignedToString(section48->unk2, true));
								node->SetAttribute("unk3", UnsignedToString(section48->unk3, true));
								node->SetAttribute("unk4", UnsignedToString(section48->unk4, true));
								node->SetAttribute("unk5", UnsignedToString(section48->unk5, true));
								node->SetAttribute("unk6", UnsignedToString(section48->unk6, true));
								node->SetAttribute("unk7", UnsignedToString(section48->unk7, true));
								node_section48->LinkEndChild(node);

								offset += sizeof(SWR_MODEL_Section48);
								section48++;
								inc++;
							}
							offset += 2 * sizeof(uint32_t);

							node_section48->SetAttribute("debugNbElements", inc);
						}

						if (section3->offset_unk52)
						{
							size_t startoffset_section52 = section3->offset_unk52 + hdr->offset_Section2;
							offset = startoffset_section52;

							TiXmlElement* node_listSection52 = new TiXmlElement("ListSection52");
							node_section3->LinkEndChild(node_listSection52);

							for (size_t m = 0; m < section3->nbElementV52; m++)
							{
								SWR_MODEL_Section52* section52 = (SWR_MODEL_Section52*)GetOffsetPtr(buf, offset, true);
								offset += sizeof(SWR_MODEL_Section52);

								TiXmlElement* node_section52 = new TiXmlElement("Section52");
								node_listSection52->LinkEndChild(node_section52);

								node = new TiXmlElement("unk0"); node->SetAttribute("u16", UnsignedToString(val16(section52->unk0), true)); node_section52->LinkEndChild(node);
								node = new TiXmlElement("unk2"); node->SetAttribute("u16", UnsignedToString(val16(section52->unk2), true)); node_section52->LinkEndChild(node);
								node = new TiXmlElement("unk4"); node->SetAttribute("u16", UnsignedToString(val16(section52->unk4), true)); node_section52->LinkEndChild(node);
								node = new TiXmlElement("unk6"); node->SetAttribute("u16", UnsignedToString(val16(section52->unk6), true)); node_section52->LinkEndChild(node);
								node = new TiXmlElement("unk8"); node->SetAttribute("u8", UnsignedToString(section52->unk8, true)); node_section52->LinkEndChild(node);
								node = new TiXmlElement("unk9"); node->SetAttribute("u8", UnsignedToString(section52->unk9, true)); node_section52->LinkEndChild(node);
								node = new TiXmlElement("unk10"); node->SetAttribute("u8", UnsignedToString(section52->unk10, true)); node_section52->LinkEndChild(node);
								node = new TiXmlElement("unk11"); node->SetAttribute("u8", UnsignedToString(section52->unk11, true)); node_section52->LinkEndChild(node);
								node = new TiXmlElement("unk12"); node->SetAttribute("u8", UnsignedToString(section52->unk12, true)); node_section52->LinkEndChild(node);
								node = new TiXmlElement("unk13"); node->SetAttribute("u8", UnsignedToString(section52->unk13, true)); node_section52->LinkEndChild(node);
								node = new TiXmlElement("unk14"); node->SetAttribute("u8", UnsignedToString(section52->unk14, true)); node_section52->LinkEndChild(node);
								node = new TiXmlElement("unk15"); node->SetAttribute("u8", UnsignedToString(section52->unk15, true)); node_section52->LinkEndChild(node);
							}
						}

						//reinverse for a another time
						section3->offset_section4 = val32(section3->offset_section4);
						section3->offset_section7 = val32(section3->offset_section7);
						section3->nbElementV90 = val16(section3->nbElementV90);
						section3->typeMode = val16(section3->typeMode);
						section3->nbElementV44 = val16(section3->nbElementV44);
						section3->nbElementV52 = val16(section3->nbElementV52);
						section3->offset_V90 = val32(section3->offset_V90);
						section3->offset_unk40 = val32(section3->offset_unk40);
						section3->offset_unk44 = val32(section3->offset_unk44);
						section3->offset_unk48 = val32(section3->offset_unk48);
						section3->offset_unk52 = val32(section3->offset_unk52);
					}

				}
				break;

				case 0x5065:
				{
					SWR_AltN_0x5065* section = (SWR_AltN_0x5065*)GetOffsetPtr(buf, offset, true);
					offset += sizeof(SWR_AltN_0x5065);

					TiXmlElement* node_section = new TiXmlElement("Section_5065");
					node_Malt->LinkEndChild(node_section);
					node = new TiXmlElement("unk_0"); node->SetAttribute("u32", UnsignedToString(val32(section->unk_0), true)); node_section->LinkEndChild(node);
				}
				break;


				case 0x5066:
				{
					SWR_AltN_0x5066* section = (SWR_AltN_0x5066*)GetOffsetPtr(buf, offset, true);
					offset += sizeof(SWR_AltN_0x5066);

					TiXmlElement* node_section = new TiXmlElement("Section_5066");
					node_Malt->LinkEndChild(node_section);
					node = new TiXmlElement("distLod_0"); node->SetAttribute("float", FloatToString(val_float(section->distLod_0))); node_section->LinkEndChild(node);
					node = new TiXmlElement("distLod_1"); node->SetAttribute("float", FloatToString(val_float(section->distLod_1))); node_section->LinkEndChild(node);
					node = new TiXmlElement("distLod_2"); node->SetAttribute("float", FloatToString(val_float(section->distLod_2))); node_section->LinkEndChild(node);
					node = new TiXmlElement("distLod_3"); node->SetAttribute("float", FloatToString(val_float(section->distLod_3))); node_section->LinkEndChild(node);
					node = new TiXmlElement("distLod_4"); node->SetAttribute("float", FloatToString(val_float(section->distLod_4))); node_section->LinkEndChild(node);
					node = new TiXmlElement("distLod_5"); node->SetAttribute("float", FloatToString(val_float(section->distLod_5))); node_section->LinkEndChild(node);
					node = new TiXmlElement("distLod_6"); node->SetAttribute("float", FloatToString(val_float(section->distLod_6))); node_section->LinkEndChild(node);
					node = new TiXmlElement("distLod_7"); node->SetAttribute("float", FloatToString(val_float(section->distLod_7))); node_section->LinkEndChild(node);

					node = new TiXmlElement("unk_8"); node->SetAttribute("float", FloatToString(val_float(section->unk_8))); node_section->LinkEndChild(node);
					node = new TiXmlElement("unk_9"); node->SetAttribute("float", FloatToString(val_float(section->unk_9))); node_section->LinkEndChild(node);
					node = new TiXmlElement("unk_10"); node->SetAttribute("float", FloatToString(val_float(section->unk_10))); node_section->LinkEndChild(node);
				}
				break;


				case 0xD064:
				{
					SWR_AltN_0xD064* section = (SWR_AltN_0xD064*)GetOffsetPtr(buf, offset, true);
					offset += sizeof(SWR_AltN_0xD064);

					TiXmlElement* node_section = new TiXmlElement("Section_D064");
					node_Malt->LinkEndChild(node_section);
					TiXmlElement* node_matrix = new TiXmlElement("Matrix3x3");
					node_section->LinkEndChild(node_matrix);

					node = new TiXmlElement("m0");
					node_matrix->LinkEndChild(node);
					node->SetAttribute("c0", FloatToString(val_float(section->m00)));
					node->SetAttribute("c1", FloatToString(val_float(section->m01)));
					node->SetAttribute("c2", FloatToString(val_float(section->m02)));

					node = new TiXmlElement("m1");
					node_matrix->LinkEndChild(node);
					node->SetAttribute("c0", FloatToString(val_float(section->m10)));
					node->SetAttribute("c1", FloatToString(val_float(section->m11)));
					node->SetAttribute("c2", FloatToString(val_float(section->m12)));

					node = new TiXmlElement("m2");
					node_matrix->LinkEndChild(node);
					node->SetAttribute("c0", FloatToString(val_float(section->m20)));
					node->SetAttribute("c1", FloatToString(val_float(section->m21)));
					node->SetAttribute("c2", FloatToString(val_float(section->m22)));


					node = new TiXmlElement("Position");
					node_section->LinkEndChild(node);
					node->SetAttribute("x", FloatToString(val_float(section->posX)));
					node->SetAttribute("y", FloatToString(val_float(section->posY)));
					node->SetAttribute("z", FloatToString(val_float(section->posZ)));
				}
				break;

				case 0xD065:
				{
					SWR_AltN_0xD065* section = (SWR_AltN_0xD065*)GetOffsetPtr(buf, offset, true);
					offset += sizeof(SWR_AltN_0xD065);

					TiXmlElement* node_section = new TiXmlElement("Section_D065");
					node_Malt->LinkEndChild(node_section);

					TiXmlElement* node_matrix = new TiXmlElement("Matrix3x3");
					node_section->LinkEndChild(node_matrix);

					node = new TiXmlElement("m0");
					node_matrix->LinkEndChild(node);
					node->SetAttribute("c0", FloatToString(val_float(section->m00))); 
					node->SetAttribute("c1", FloatToString(val_float(section->m01)));
					node->SetAttribute("c2", FloatToString(val_float(section->m02)));
					
					node = new TiXmlElement("m1");
					node_matrix->LinkEndChild(node);
					node->SetAttribute("c0", FloatToString(val_float(section->m10)));
					node->SetAttribute("c1", FloatToString(val_float(section->m11)));
					node->SetAttribute("c2", FloatToString(val_float(section->m12)));

					node = new TiXmlElement("m2");
					node_matrix->LinkEndChild(node);
					node->SetAttribute("c0", FloatToString(val_float(section->m20)));
					node->SetAttribute("c1", FloatToString(val_float(section->m21)));
					node->SetAttribute("c2", FloatToString(val_float(section->m22)));


					node = new TiXmlElement("Position");
					node_section->LinkEndChild(node);
					node->SetAttribute("x", FloatToString(val_float(section->posX)));
					node->SetAttribute("y", FloatToString(val_float(section->posY)));
					node->SetAttribute("z", FloatToString(val_float(section->posZ)));

					node = new TiXmlElement("Unknow12_Vector3");
					node_section->LinkEndChild(node);
					node->SetAttribute("x", FloatToString(val_float(section->unk12_X)));
					node->SetAttribute("y", FloatToString(val_float(section->unk12_Y)));
					node->SetAttribute("z", FloatToString(val_float(section->unk12_Z)));
				}
				break;

				case 0xD066:
				{
					SWR_AltN_0xD066* section = (SWR_AltN_0xD066*)GetOffsetPtr(buf, offset, true);
					offset += sizeof(SWR_AltN_0xD066);

					TiXmlElement* node_section = new TiXmlElement("Section_D066");
					node_Malt->LinkEndChild(node_section);
					node = new TiXmlElement("unk_0"); node->SetAttribute("u16", UnsignedToString(val16(section->unk_0), true)); node_section->LinkEndChild(node);
					node = new TiXmlElement("unk_1"); node->SetAttribute("u16", UnsignedToString(val16(section->unk_1), true)); node_section->LinkEndChild(node);

					node = new TiXmlElement("unk_2"); node->SetAttribute("float", FloatToString(val_float(section->unk_2))); node_section->LinkEndChild(node);
					node = new TiXmlElement("unk_3"); node->SetAttribute("float", FloatToString(val_float(section->unk_3))); node_section->LinkEndChild(node);
					node = new TiXmlElement("unk_4"); node->SetAttribute("float", FloatToString(val_float(section->unk_4))); node_section->LinkEndChild(node);
				}
				break;

				default:
					break;
				}



				// Recursively parse children if this has any ???
				if ((hdr_AltN->flags & 0x4000) && (hdr_AltN->offset_Childs))				// 0x5xxx or 0xDxxxx (for 0x3xxx the child are struct_V16)
				{
					size_t startoffset_Child_listOffset = hdr_AltN->offset_Childs + hdr->offset_Section2;
					offset = startoffset_Child_listOffset;

					uint32_t* listOffsetAltN_Child = (uint32_t*)GetOffsetPtr(buf, offset, true);

					TiXmlElement* node_section = new TiXmlElement("ListChild");
					node_Malt->LinkEndChild(node_section);

					for (size_t k = 0; k < hdr_AltN->nb_Childs; k++)
					{
						offset += sizeof(uint32_t);

						if (listOffsetAltN_Child[k] == 0)
							continue;

						node = new TiXmlElement("Child"); node->SetAttribute("offset", UnsignedToString(val32(listOffsetAltN_Child[k]) + hdr->offset_Section2, true)); node_section->LinkEndChild(node);

						listRecusiveAltN.push_back(val32(listOffsetAltN_Child[k]) + hdr->offset_Section2);
					}
				}

				//reinverse for another pass on the same
				hdr_AltN->flags = val32(hdr_AltN->flags);
				hdr_AltN->nb_Childs = val32(hdr_AltN->nb_Childs);
				hdr_AltN->offset_Childs = val32(hdr_AltN->offset_Childs);

			}
		}





		//-----------------------  Anim :

		
		TiXmlElement* node_listAnim = new TiXmlElement("ListAnim");
		node_model->LinkEndChild(node_listAnim);


		size_t nbAnim = listPointer_Anim.size();
		for (size_t inc_Anim = 0; inc_Anim < nbAnim; inc_Anim++)
		{
			size_t startSectionAnim = listPointer_Anim.at(inc_Anim);
			offset = startSectionAnim;

			SWR_Anim_Header* hdr_anim = (SWR_Anim_Header*)GetOffsetPtr(buf, offset, true);
			offset += sizeof(SWR_Anim_Header);
			hdr_anim->nbKeyFrames = val32(hdr_anim->nbKeyFrames);
			hdr_anim->offset_times = val32(hdr_anim->offset_times);
			hdr_anim->offset_values = val32(hdr_anim->offset_values);
			hdr_anim->offset_AltN = val32(hdr_anim->offset_AltN);


			TiXmlElement* node_Anim = new TiXmlElement("Anim");
			node_listAnim->LinkEndChild(node_Anim);
			
			node = new TiXmlElement("unk0");
			for(size_t j=0;j<61;j++)
				node->SetAttribute(string("i_") + std::to_string(j), UnsignedToString(val32(hdr_anim->unk0[j]), true));
			node_Anim->LinkEndChild(node);

			node = new TiXmlElement("unk1_X"); node->SetAttribute("float", FloatToString(val_float(hdr_anim->unk1_X))); node_Anim->LinkEndChild(node);
			node = new TiXmlElement("unk1_Y"); node->SetAttribute("float", FloatToString(val_float(hdr_anim->unk1_Y))); node_Anim->LinkEndChild(node);
			node = new TiXmlElement("unk1_Z"); node->SetAttribute("float", FloatToString(val_float(hdr_anim->unk1_Z))); node_Anim->LinkEndChild(node);
			node = new TiXmlElement("unk2"); node->SetAttribute("u8", UnsignedToString(hdr_anim->unk2, true)); node_Anim->LinkEndChild(node);
			node = new TiXmlElement("unk3"); node->SetAttribute("u8", UnsignedToString(hdr_anim->unk3, true)); node_Anim->LinkEndChild(node);
			node = new TiXmlElement("unk4"); node->SetAttribute("u8", UnsignedToString(hdr_anim->unk4, true)); node_Anim->LinkEndChild(node);
			node = new TiXmlElement("flags"); node->SetAttribute("u8", UnsignedToString(hdr_anim->flags, true)); node_Anim->LinkEndChild(node);
			node = new TiXmlElement("unk5_X"); node->SetAttribute("float", FloatToString(val_float(hdr_anim->unk5_X))); node_Anim->LinkEndChild(node);
			node = new TiXmlElement("unk5_Y"); node->SetAttribute("float", FloatToString(val_float(hdr_anim->unk5_Y))); node_Anim->LinkEndChild(node);
			node = new TiXmlElement("unk5_Z"); node->SetAttribute("float", FloatToString(val_float(hdr_anim->unk5_Z))); node_Anim->LinkEndChild(node);
			node = new TiXmlElement("unk6"); node->SetAttribute("u32", UnsignedToString(val32(hdr_anim->unk6), true)); node_Anim->LinkEndChild(node);
			node = new TiXmlElement("unk7"); node->SetAttribute("u32", UnsignedToString(val32(hdr_anim->unk7), true)); node_Anim->LinkEndChild(node);
			node = new TiXmlElement("unk8"); node->SetAttribute("u32", UnsignedToString(val32(hdr_anim->unk8), true)); node_Anim->LinkEndChild(node);

			//todo remove after solve case flags 2, 12, and 35
			node = new TiXmlElement("nbKeyFrames"); node->SetAttribute("u32", UnsignedToString(hdr_anim->nbKeyFrames, false)); node_Anim->LinkEndChild(node);
			
			std::vector<float> listKeyframesTimes;
			if (hdr_anim->offset_times)
			{
				size_t startSectionAnim_Times = hdr_anim->offset_times + hdr->offset_Section2;
				offset = startSectionAnim_Times;

				float* values = (float*)GetOffsetPtr(buf, offset, true);
				for (size_t j = 0; j < hdr_anim->nbKeyFrames; j++)
				{
					listKeyframesTimes.push_back(val_float(values[j]));
					offset += sizeof(float);
				}
			}

			if (hdr_anim->offset_values)
			{
				size_t startSectionAnim_Values = hdr_anim->offset_values + hdr->offset_Section2;
				offset = startSectionAnim_Values;

				size_t nbComponents = 0;
				switch (hdr_anim->flags & 0x0F)
				{
				case 1: case 0xB: case 0xC:	nbComponents = 1; break;
				case 4:						nbComponents = 2; break;
				case 7: case 9: case 0xA:	nbComponents = 3; break;
				case 6: case 8:				nbComponents = 4; break;


				case 2:
				{
					offset = hdr_anim->offset_AltN + hdr->offset_Section2;
					SWR_Anim_Values_case2_Header* hdr_anim2 = (SWR_Anim_Values_case2_Header*)GetOffsetPtr(buf, offset, true);

					TiXmlElement* node_listKeyframes = new TiXmlElement("ListKeyframes");
					node_listKeyframes->SetAttribute("offset_section4_targeted", UnsignedToString(val32(hdr_anim2->offset_section4), true));
					node_listKeyframes->SetAttribute("case2__unk0", UnsignedToString(val32(hdr_anim2->unk0), true) );
					node_Anim->LinkEndChild(node_listKeyframes);


					offset = hdr_anim->offset_values + hdr->offset_Section2;
					uint32_t* listOffset = (uint32_t*)GetOffsetPtr(buf, offset, true);
					
					for (size_t j = 0; j < hdr_anim->nbKeyFrames; j++)
					{
						size_t startoffset_section5 = val32(listOffset[j]) + hdr->offset_Section2;
						offset = startoffset_section5;

						TiXmlElement* node_Kf = new TiXmlElement("Keyframe");
						node_listKeyframes->LinkEndChild(node_Kf);

						node_Kf->SetAttribute("time", FloatToString(listKeyframesTimes.at(j)));

						SWR_Anim_Values_case2* section = (SWR_Anim_Values_case2*)GetOffsetPtr(buf, offset, true);

						SWR_MODEL_Section5* section5 = (SWR_MODEL_Section5*)GetOffsetPtr(buf, offset, true);
						offset += sizeof(SWR_MODEL_Section5);


						TiXmlElement* node_section5 = new TiXmlElement("Section5");
						node_Kf->LinkEndChild(node_section5);

						node = new TiXmlElement("unk0"); node->SetAttribute("u32", UnsignedToString(val32(section5->unk0), true)); node_section5->LinkEndChild(node);
						node = new TiXmlElement("unk4"); node->SetAttribute("u16", UnsignedToString(val16(section5->unk4), true)); node_section5->LinkEndChild(node);
						node = new TiXmlElement("unk6"); node->SetAttribute("u16", UnsignedToString(val16(section5->unk6), true)); node_section5->LinkEndChild(node);
						node = new TiXmlElement("unk8_0"); node->SetAttribute("u16", UnsignedToString(val16(section5->unk8[0]), true)); node_section5->LinkEndChild(node);
						node = new TiXmlElement("unk8_1"); node->SetAttribute("u16", UnsignedToString(val16(section5->unk8[1]), true)); node_section5->LinkEndChild(node);
						node = new TiXmlElement("unk12_0"); node->SetAttribute("u8", UnsignedToString(section5->unk12[0], true)); node_section5->LinkEndChild(node);
						node = new TiXmlElement("unk12_1"); node->SetAttribute("u8", UnsignedToString(section5->unk12[1], true)); node_section5->LinkEndChild(node);
						node = new TiXmlElement("unk12_2"); node->SetAttribute("u8", UnsignedToString(section5->unk12[2], true)); node_section5->LinkEndChild(node);
						node = new TiXmlElement("unk12_3"); node->SetAttribute("u8", UnsignedToString(section5->unk12[3], true)); node_section5->LinkEndChild(node);
						node = new TiXmlElement("unk16"); node->SetAttribute("u16", UnsignedToString(val16(section5->unk16), true)); node_section5->LinkEndChild(node);
						node = new TiXmlElement("unk18"); node->SetAttribute("u16", UnsignedToString(val16(section5->unk18), true)); node_section5->LinkEndChild(node);
						node = new TiXmlElement("unk20"); node->SetAttribute("u16", UnsignedToString(val16(section5->unk20), true)); node_section5->LinkEndChild(node);
						node = new TiXmlElement("unk22"); node->SetAttribute("u16", UnsignedToString(val16(section5->unk22), true)); node_section5->LinkEndChild(node);
						node = new TiXmlElement("unk24"); node->SetAttribute("u16", UnsignedToString(val16(section5->unk24), true)); node_section5->LinkEndChild(node);
						node = new TiXmlElement("unk26"); node->SetAttribute("u16", UnsignedToString(val16(section5->unk26), true)); node_section5->LinkEndChild(node);
						node = new TiXmlElement("unk48"); node->SetAttribute("u32", UnsignedToString(val32(section5->unk48), true)); node_section5->LinkEndChild(node);
						node = new TiXmlElement("unk52"); node->SetAttribute("u32", UnsignedToString(val32(section5->unk52), true)); node_section5->LinkEndChild(node);
						node = new TiXmlElement("unk56"); node->SetAttribute("u8", UnsignedToString(section5->unk56, true)); node_section5->LinkEndChild(node);
						node = new TiXmlElement("unk57"); node->SetAttribute("u8", UnsignedToString(section5->unk57, true)); node_section5->LinkEndChild(node);
						node = new TiXmlElement("unk58"); node->SetAttribute("u16", UnsignedToString(val16(section5->unk58), true)); node_section5->LinkEndChild(node);
						node = new TiXmlElement("unk60"); node->SetAttribute("u32", UnsignedToString(val32(section5->unk60), true)); node_section5->LinkEndChild(node);

						for (size_t m = 0; m < 5; m++)
						{
							if (!section5->offset_Section5_b[m])
								continue;
							
							size_t startoffset_section5_b = val32(section5->offset_Section5_b[m]) + hdr->offset_Section2;
							offset = startoffset_section5_b;

							SWR_MODEL_Section5_b* section5_b = (SWR_MODEL_Section5_b*)GetOffsetPtr(buf, offset, true);

							offset += sizeof(SWR_MODEL_Section5_b);

							TiXmlElement* node_section5b = new TiXmlElement("Section5b");
							node_section5->LinkEndChild(node_section5b);

							node = new TiXmlElement("unk0"); node->SetAttribute("u16", UnsignedToString(val16(section5_b->unk0), true)); node_section5b->LinkEndChild(node);
							node = new TiXmlElement("unk2"); node->SetAttribute("u8", UnsignedToString(section5_b->unk2, true)); node_section5b->LinkEndChild(node);
							node = new TiXmlElement("unk3"); node->SetAttribute("u8", UnsignedToString(section5_b->unk3, true)); node_section5b->LinkEndChild(node);
							node = new TiXmlElement("unk4"); node->SetAttribute("u8", UnsignedToString(section5_b->unk4, true)); node_section5b->LinkEndChild(node);
							node = new TiXmlElement("unk5"); node->SetAttribute("u8", UnsignedToString(section5_b->unk5, true)); node_section5b->LinkEndChild(node);
							node = new TiXmlElement("unk6_a"); node->SetAttribute("u8", UnsignedToString(val16(section5_b->unk6_a), true)); node_section5b->LinkEndChild(node);
							node = new TiXmlElement("unk6_b"); node->SetAttribute("u8", UnsignedToString(val16(section5_b->unk6_b), true)); node_section5b->LinkEndChild(node);
							node = new TiXmlElement("unk8"); node->SetAttribute("u32", UnsignedToString(val32(section5_b->unk8), true)); node_section5b->LinkEndChild(node);
							node = new TiXmlElement("unk12"); node->SetAttribute("u16", UnsignedToString(val16(section5_b->unk12), true)); node_section5b->LinkEndChild(node);
							node = new TiXmlElement("unk14"); node->SetAttribute("u16", UnsignedToString(val16(section5_b->unk14), true)); node_section5b->LinkEndChild(node);
						}

						
					}
				}

				case 5:
				{
					// strange things for offset_values and offset_AltN Todo test if it's float16:
					node = new TiXmlElement("offset_values_case5"); node->SetAttribute("u32", UnsignedToString(hdr_anim->offset_values, true)); node_Anim->LinkEndChild(node);
					node = new TiXmlElement("offset_AltN_case5"); node->SetAttribute("u32", UnsignedToString(hdr_anim->offset_AltN, true)); node_Anim->LinkEndChild(node);
				}break;

				default:
				{
					::printf("Warning: Unknowed animation flags for component %s. skipped.\n", UnsignedToString(hdr_anim->flags, true).c_str());
					notifyWarning();
				}break;
				}

				//nbComponents = 0;		//test Anima Todo remove


				TiXmlElement* node_listKeyframes = new TiXmlElement("ListKeyframes");
				node_listKeyframes->SetAttribute("nbComponents", nbComponents);
				node_Anim->LinkEndChild(node_listKeyframes);

				if (nbComponents != 0)
				{
					float* values = (float*)GetOffsetPtr(buf, offset, true);
					size_t inc = 0;

					for (size_t j = 0; j < hdr_anim->nbKeyFrames; j++)
					{
						TiXmlElement* node_Kf = new TiXmlElement("Keyframe");
						node_listKeyframes->LinkEndChild(node_Kf);

						node_Kf->SetAttribute("time", FloatToString(listKeyframesTimes.at(j)));

						if (nbComponents != 4)
						{
							node_Kf->SetAttribute( (nbComponents != 1) ? "x" : "value", FloatToString(val_float(values[inc++])));
							offset += sizeof(float);

							if (nbComponents > 1)
							{
								node_Kf->SetAttribute("y", FloatToString(val_float(values[inc++])));
								offset += sizeof(float);
							}
							if (nbComponents > 2)
							{
								node_Kf->SetAttribute("z", FloatToString(val_float(values[inc++])));
								offset += sizeof(float);
							}

						}else {			//apparently it's quaternion, and the order is W XYZ, to be simple ...

							float w = val_float(values[inc++]);
							node_Kf->SetAttribute("x", FloatToString(val_float(values[inc++])));
							node_Kf->SetAttribute("y", FloatToString(val_float(values[inc++])));
							node_Kf->SetAttribute("z", FloatToString(val_float(values[inc++])));
							node_Kf->SetAttribute("w", FloatToString(w));
							offset += 4 * sizeof(float);
						}

					}
				}
			}

			//reinverse for another time
			hdr_anim->nbKeyFrames = val32(hdr_anim->nbKeyFrames);
			hdr_anim->offset_times = val32(hdr_anim->offset_times);
			hdr_anim->offset_values = val32(hdr_anim->offset_values);
			hdr_anim->offset_AltN = val32(hdr_anim->offset_AltN);
		}
	}
}







/////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// wxHexEditor coloration ////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////


/*-------------------------------------------------------------------------------\
|                             save_Coloration		                             |
\-------------------------------------------------------------------------------*/
void Swr_Model::save_Coloration(string filename, bool show_error)
{
	uint8_t *buf;
	size_t size;

	buf = ReadFile(filename, &size, show_error);
	if (!buf)
		return;

	TiXmlDocument *doc = new TiXmlDocument();
	TiXmlDeclaration* decl = new TiXmlDeclaration("1.0", "UTF-8", "");
	doc->LinkEndChild(decl);

	TiXmlElement *root = new TiXmlElement("wxHexEditor_XML_TAG");


	TiXmlElement* filename_node = new TiXmlElement("filename");
	EMO_BaseFile::WriteParamString(filename_node, "path", filename);



#if 0
	//Split the main file, into one file by Model, because of TinyXml, Todo commment.
	{
		big_endian = true;
		std::vector<size_t> listBytesAllreadyTagged;
		listBytesAllreadyTagged.resize(size, (size_t)-1);				//to check override of the same byte (overflow)

		size_t nbModels = val32(*(uint32_t*)buf);

		size_t offset = sizeof(uint32_t);
		size_t startoffsetModelHeader = offset;
		for (size_t i = 0; i < nbModels; i++)
		{
			offset = startoffsetModelHeader + i * sizeof(SWR_MODELHeader);

			SWR_MODELHeader_Used* hdr = (SWR_MODELHeader_Used*)(buf + offset);
			hdr->offset_Section1 = val32(hdr->offset_Section1);
			hdr->offset_Section2 = val32(hdr->offset_Section2);
			size_t offset_NextHeader_Section1 = val32(hdr->offset_NextHeader_Section1);

			size_t sizeSection1 = hdr->offset_Section2 - hdr->offset_Section1;
			size_t sizeSection2 = offset_NextHeader_Section1 - hdr->offset_Section2;

			{
				size_t filesize = 4 * sizeof(uint32_t) + sizeSection1 + sizeSection2;

				uint8_t *buf_tmp = new uint8_t[filesize];
				if (!buf_tmp)
				{
					printf("%s: Memory allocation error (0x%x)\n", FUNCNAME, filesize);
					notifyError();
					return;
				}
				uint32_t* buf_u32 = (uint32_t*)buf_tmp;
				buf_u32[0] = val32(1);
				buf_u32[1] = val32(0x10);
				buf_u32[2] = val32(0x10 + sizeSection1);
				buf_u32[3] = val32(0x10 + sizeSection1 + sizeSection2);
				memcpy(buf_tmp + 4 *sizeof(uint32_t), buf + hdr->offset_Section1, sizeSection1);
				memcpy(buf_tmp + 4 * sizeof(uint32_t) + sizeSection1, buf + hdr->offset_Section2, sizeSection2);

				bool ret = WriteFileBool(filename +"_"+ UnsignedToString(i, false) +".bin", buf_tmp, filesize);
				delete[] buf_tmp;
			}
		}
		return; 
	}
#endif
	
	
	try
	{
		write_Coloration(filename_node, buf, size);
	}catch (...) {

	}


	root->LinkEndChild(filename_node);
	doc->LinkEndChild(root);



	delete[] buf;

	doc->SaveFile(filename + ".tags");

	return;
}




/*-------------------------------------------------------------------------------\
|                             write_Coloration				                     |
\-------------------------------------------------------------------------------*/
void Swr_Model::write_Coloration(TiXmlElement *parent, const uint8_t *buf, size_t size)
{
	big_endian = true;
	std::vector<size_t> listBytesAllreadyTagged;
	listBytesAllreadyTagged.resize(size, (size_t)-1);				//to check override of the same byte (overflow)

	size_t idTag = 0;
	size_t offset = 0;
	size_t incSection = 0;
	size_t incParam = 0;


	
	size_t nbModels = val32(*(uint32_t*)buf);

	write_Coloration_Tag("nbModels", "uint32_t", "", offset, sizeof(uint32_t), "SWR_MODELHeader", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(uint32_t);

	size_t startoffsetModelHeader = offset;
	for (size_t i = 0; i < nbModels; i++)
	{
		incSection = 0;
		incParam = 0;
		
		offset = startoffsetModelHeader + i * sizeof(SWR_MODELHeader);

		SWR_MODELHeader_Used* hdr = (SWR_MODELHeader_Used*)(buf + offset);
		hdr->offset_Section1 = val32(hdr->offset_Section1);
		hdr->offset_Section2 = val32(hdr->offset_Section2);
		size_t offset_NextHeader_Section1 = val32(hdr->offset_NextHeader_Section1);

		write_Coloration_Tag("offset_Section1", "uint32_t", "Materials or Textures descriptors/mask", offset, sizeof(uint32_t), "SWR_MODELHeader", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, i); offset += sizeof(uint32_t);
		write_Coloration_Tag("offset_Section2", "uint32_t", "", offset, sizeof(uint32_t), "SWR_MODELHeader", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, i); offset += sizeof(uint32_t);
		


		//Section1 
		std::vector<uint32_t> dataSection1;
		uint32_t* section1 = (uint32_t*)GetOffsetPtr(buf, hdr->offset_Section1, true);
		offset = hdr->offset_Section1;
		incSection++;
		incParam = 0;
				
		size_t nbSection1Elements = (hdr->offset_Section2 - hdr->offset_Section1) / sizeof(uint32_t);
		for (size_t j = 0; j < nbSection1Elements; j++)
		{
			dataSection1.push_back(section1[j]);
			write_Coloration_Tag("bitMaskForMaterialOrTexture", "uint32_t", "", offset, sizeof(uint32_t), "Section1", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, j); offset += sizeof(uint32_t);
		}



		//Section2
		SWR_MODEL_Section2_Header* hdr_section2 = (SWR_MODEL_Section2_Header*)GetOffsetPtr(buf, hdr->offset_Section2, true);
		offset = hdr->offset_Section2;
		size_t sizeSection2 = offset_NextHeader_Section1 - hdr->offset_Section2;

		incSection++;
		incParam = 0;
		write_Coloration_Tag("signature", "string", "", offset, 4 * sizeof(char), "Section2_Header", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, i);	offset += 4 * sizeof(char);

		if (memcmp(hdr_section2->signature, SWR_MODEL_SIGNATURE_COMPRESSED, 4) == 0)
		{
			::printf("Warning: Comp (for Compressed data) is not take care. did you use data from Pc version ? skipped.\n");
			notifyWarning();
			continue;
		}

		//Todo after : take care of "Comp" Compressed
		
		//Todo Take care of Material/textures informations instead just pass :
		/*
		// Loop over each mesh [material?] (?)
		for (int32_t i = 0; i < nbUint32; i++) 
		{
			// Check if this mesh is textured
			if ((1 << (31 - (i & 0x1F))) & data_ModelA[i >> 5]) 
			{
				data_ModelB_uint32[i] = swap32(data_ModelB_uint32[i]);

				if ((data_ModelB_uint32[i] & 0xFF000000) == 0x0A000000)
				{
					// Load texture
					setTextureHelper(nbUint32, data_ModelB_uint32[i] & 0x00FFFFFF, (char**)&data_ModelB_uint32[i], (int*)&data_ModelB_uint32[i + 1]);

				}else if (data_ModelB_uint32[i] != 0x00000000) {
					// Texture is already in memory, so point into an existing buffer ???
					data_ModelB_uint32[i] = (unsigned int)data_ModelB + data_ModelB_uint32[i];					// a utin32 informations from a size it become a endOffset adress.
				}
			}
		}
		*/


		if ((memcmp(hdr_section2->signature, SWR_MODEL_SIGNATURE_MODEL, 4) != 0) &&
			(memcmp(hdr_section2->signature, SWR_MODEL_SIGNATURE_TRACK, 4) != 0) &&
			(memcmp(hdr_section2->signature, SWR_MODEL_SIGNATURE_POD, 4) != 0) &&
			(memcmp(hdr_section2->signature, SWR_MODEL_SIGNATURE_PART, 4) != 0) &&
			(memcmp(hdr_section2->signature, SWR_MODEL_SIGNATURE_SCENE, 4) != 0) &&
			(memcmp(hdr_section2->signature, SWR_MODEL_SIGNATURE_MAlt, 4) != 0) &&
			(memcmp(hdr_section2->signature, SWR_MODEL_SIGNATURE_Pupp, 4) != 0)
			)
		{
			::printf("Warning: Unknowed Section2_header Signature :%c%c%c%c skipped.\n", hdr_section2->signature[0], hdr_section2->signature[1], hdr_section2->signature[2], hdr_section2->signature[3]);
			notifyWarning();
			continue;
		}



		std::vector<size_t> listPointer_AltN;
		std::vector<size_t> listPointer_Anim;

		uint32_t* section2_unknowParts = (uint32_t*)GetOffsetPtr(buf, offset, true);
		while (*section2_unknowParts != 0xFFFFFFFF)
		{
			if ((*section2_unknowParts != 0)&&(val32(*section2_unknowParts)<sizeSection2)&&(!checkDuplication(val32(*section2_unknowParts) + hdr->offset_Section2, listPointer_AltN)))
				listPointer_AltN.push_back(val32(*section2_unknowParts) + hdr->offset_Section2);
			
			write_Coloration_Tag("possible_offset_section", "uint32_t", (*section2_unknowParts != 0) ? (" => "+ UnsignedToString(val32(*section2_unknowParts) + hdr->offset_Section2, true)): "", offset, sizeof(uint32_t), "Section2_Header", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(uint32_t);

			section2_unknowParts++;
		}
		write_Coloration_Tag("EndListPointer", "uint32_t", "", offset, sizeof(uint32_t), "Section2_Header", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(uint32_t);




		bool endFound = false;
		while (!endFound)
		{
			incSection++;
			incParam = 0;

			SWR_MODEL_Section2_Header* hdr_section2_sub = (SWR_MODEL_Section2_Header*)GetOffsetPtr(buf, offset, true);
			write_Coloration_Tag("signature", "string", "", offset, 4 * sizeof(char), "Section2_SubHeader", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged);	offset += 4 * sizeof(char);

			if ((memcmp(hdr_section2_sub->signature, SWR_MODEL_SIGNATURE_ALTN, 4) != 0) &&
				(memcmp(hdr_section2_sub->signature, SWR_MODEL_SIGNATURE_DATA, 4) != 0) &&
				(memcmp(hdr_section2_sub->signature, SWR_MODEL_SIGNATURE_ANIM, 4) != 0) &&
				(memcmp(hdr_section2_sub->signature, SWR_MODEL_SIGNATURE_HEND, 4) != 0)
				)
			{
				::printf("Warning: Unknowed Section2_SubHeader Signature :%c%c%c%c skipped.\n", hdr_section2_sub->signature[0], hdr_section2_sub->signature[1], hdr_section2_sub->signature[2], hdr_section2_sub->signature[3]);
				notifyWarning();
				break;

			}else if (memcmp(hdr_section2_sub->signature, SWR_MODEL_SIGNATURE_ANIM, 4) == 0) {

				
				size_t startoffset_Anim = offset;
				uint32_t* listOffsetAnim = (uint32_t*)GetOffsetPtr(buf, startoffset_Anim, true);

				size_t inc_Anim = 0;
				while (listOffsetAnim[inc_Anim] != 0)
				{
					listOffsetAnim[inc_Anim] = val32(listOffsetAnim[inc_Anim]);

					if (!checkDuplication(listOffsetAnim[inc_Anim] + hdr->offset_Section2, listPointer_Anim))
						listPointer_Anim.push_back(listOffsetAnim[inc_Anim] + hdr->offset_Section2);

					write_Coloration_Tag("offset_SectionAltN", "uint32_t", " => 0x" + UnsignedToString(listOffsetAnim[inc_Anim] + hdr->offset_Section2, true), startoffset_Anim + inc_Anim * sizeof(uint32_t), sizeof(uint32_t), "Section2_SubHeader", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, inc_Anim); offset += sizeof(uint32_t);

					inc_Anim++;

					if (listOffsetAnim[inc_Anim] == 0)
						break;
				}
				write_Coloration_Tag("EndOfList", "uint32_t", "", startoffset_Anim + inc_Anim * sizeof(uint32_t), sizeof(uint32_t), "Section2_SubHeader", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(uint32_t);



			}else if (memcmp(hdr_section2_sub->signature, SWR_MODEL_SIGNATURE_DATA, 4) == 0){


				size_t startoffset_Data = offset;
				
				size_t nbDatas = val32(*(uint32_t*)GetOffsetPtr(buf, startoffset_Data, true));
				write_Coloration_Tag("nbDatas", "uint32_t", "", offset, sizeof(uint32_t), "Section2_SubHeader", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(uint32_t);
				
				SWR_Data* datas = (SWR_Data*)GetOffsetPtr(buf, offset, true);
				
				for (size_t j = 0; j < nbDatas; j++)
				{
					write_Coloration_Tag("unk0", "uint8_t", "", offset, sizeof(uint8_t), "SWR_Data", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(uint8_t);
					write_Coloration_Tag("unk1", "uint8_t", "", offset, sizeof(uint8_t), "SWR_Data", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(uint8_t);
					write_Coloration_Tag("unk2", "uint8_t", "", offset, sizeof(uint8_t), "SWR_Data", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(uint8_t);
					write_Coloration_Tag("unk3", "uint8_t", "", offset, sizeof(uint8_t), "SWR_Data", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(uint8_t);
				}

				//todo understand data is for what ? linked to another files ?

			}else if (memcmp(hdr_section2_sub->signature, SWR_MODEL_SIGNATURE_ALTN, 4) == 0) {


				size_t startoffset_AltN = offset;
				uint32_t* listOffsetAltN = (uint32_t*)GetOffsetPtr(buf, startoffset_AltN, true);

				size_t inc_AltN = 0;
				while (listOffsetAltN[inc_AltN] != 0)
				{
					listOffsetAltN[inc_AltN] = val32(listOffsetAltN[inc_AltN]);

					if (!checkDuplication(listOffsetAltN[inc_AltN] + hdr->offset_Section2, listPointer_AltN))
						listPointer_AltN.push_back(listOffsetAltN[inc_AltN] + hdr->offset_Section2);

					write_Coloration_Tag("offset_SectionAltN", "uint32_t", " => 0x" + UnsignedToString(listOffsetAltN[inc_AltN] + hdr->offset_Section2, true), startoffset_AltN + inc_AltN * sizeof(uint32_t), sizeof(uint32_t), "Section2_SubHeader", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, inc_AltN); offset += sizeof(uint32_t);

					inc_AltN++;
					
					if (listOffsetAltN[inc_AltN] == 0)
						break;
				}
				write_Coloration_Tag("EndOfList", "uint32_t", "", startoffset_AltN + inc_AltN * sizeof(uint32_t), sizeof(uint32_t), "Section2_SubHeader", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(uint32_t);

			}else {		// else "Hend" => normal exit.
				endFound = true;
			}
		}
		

		//saddely , it's could have a Malt just after Hend, never referenced (cf Model_115), So we test to add it.
		// hope the filter on first flags could avoid trouble.
		if (!checkDuplication(offset, listPointer_AltN))
			listPointer_AltN.push_back(offset);

		
		
		//-----------------------  Malt /AltN :

		std::vector<size_t> listToAvoidDuplication;

		size_t nbAltN = listPointer_AltN.size();
		for(size_t inc_AltN = 0; inc_AltN< nbAltN ; inc_AltN++)
		{
			size_t startSectionAltN = listPointer_AltN.at(inc_AltN);
			offset = startSectionAltN;

			incSection = 3;			//for having 4 in for
			incParam = 0;

			std::vector<size_t> listRecusiveAltN;
			listRecusiveAltN.push_back(offset);

			for(size_t j=0;j<listRecusiveAltN.size();j++)
			{
				offset = listRecusiveAltN.at(j);

				if (checkDuplication(offset, listToAvoidDuplication))
					continue;
				listToAvoidDuplication.push_back(offset);


				incSection++;
				incParam = 0;

				if (*(uint32_t*)GetOffsetPtr(buf, offset, true) == 0)
				{
					//write_Coloration_Tag("badPointerComeHere", "uint32_t", " Todo why ?", offset, sizeof(uint32_t), "SWR_AltN_Header", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, j);
					continue;
				}

				SWR_AltN_Header* hdr_AltN = (SWR_AltN_Header*)GetOffsetPtr(buf, offset, true);
				hdr_AltN->flags = val32(hdr_AltN->flags);
				hdr_AltN->nb_Childs = val32(hdr_AltN->nb_Childs);
				hdr_AltN->offset_Childs = val32(hdr_AltN->offset_Childs);

				write_Coloration_Tag("flags", "uint32_t", "values founded : 0x3064 (most x7680, look like geometry), 0x5064 (third x 1795, look like just a node in hiererachy, without extra datas than Malt Header), 0x5065 (x52, 0 1 -1 ?), 0x5066 (x75, look like Lod definitions, and be linked to 0xd064), 0xd064 (x75, it's a Transform, look like be linked to 0x5066),  0xd065 (second x5413, look like tranform + a unknow Position), 0xd066 (x78)", offset, sizeof(uint32_t), "SWR_AltN_Header", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, j); offset += sizeof(uint32_t);
				write_Coloration_Tag("unk0", "uint32_t", "look like flags, 0xffffffff (most)", offset, sizeof(uint32_t), "SWR_AltN_Header", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, j); offset += sizeof(uint32_t);
				write_Coloration_Tag("unk1", "uint32_t", "look also like flags, 0xfffffffd (most) ", offset, sizeof(uint32_t), "SWR_AltN_Header", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, j); offset += sizeof(uint32_t);
				write_Coloration_Tag("unk_2_a", "uint8_t", "look like could be splitted in 2 uint4 : 0 (most), 1 or 2 for the first. 0 (most) 3 or 0xb for the second. So it's look like flags.", offset, sizeof(uint8_t), "SWR_AltN_Header", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, j); offset += sizeof(uint8_t);
				write_Coloration_Tag("unk_2_b", "uint8_t", "always 0", offset, sizeof(uint8_t), "SWR_AltN_Header", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, j); offset += sizeof(uint8_t);
				write_Coloration_Tag("unk3", "uint16_t", "always 0", offset, sizeof(uint16_t), "SWR_AltN_Header", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, j); offset += sizeof(uint16_t);
				write_Coloration_Tag("unk4", "uint32_t", "always 0", offset, sizeof(uint32_t), "SWR_AltN_Header", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, j); offset += sizeof(uint32_t);
				write_Coloration_Tag("nb_Childs", "uint32_t", "", offset, sizeof(uint32_t), "SWR_AltN_Header", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, j); offset += sizeof(uint32_t);
				write_Coloration_Tag("offset_Childs", "uint32_t", " => 0x"+ UnsignedToString(hdr_AltN->offset_Childs + hdr->offset_Section2, true), offset, sizeof(uint32_t), "SWR_AltN_Header", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, j); offset += sizeof(uint32_t);


				//todo: better understand flags to avoid the big switch, if it's possible.

				switch (hdr_AltN->flags)
				{
					case 0x3064:
					{
						SWR_AltN_0x3064* section = (SWR_AltN_0x3064*)GetOffsetPtr(buf, offset, true);

						write_Coloration_Tag("minX", "float", "", offset, sizeof(float), "SWR_AltN_0x3064", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(float);
						write_Coloration_Tag("minY", "float", "", offset, sizeof(float), "SWR_AltN_0x3064", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(float);
						write_Coloration_Tag("minZ", "float", "", offset, sizeof(float), "SWR_AltN_0x3064", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(float);
						write_Coloration_Tag("maxX", "float", "", offset, sizeof(float), "SWR_AltN_0x3064", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(float);
						write_Coloration_Tag("maxY", "float", "", offset, sizeof(float), "SWR_AltN_0x3064", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(float);
						write_Coloration_Tag("maxZ", "float", "", offset, sizeof(float), "SWR_AltN_0x3064", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(float);
						write_Coloration_Tag("unk0", "uint32_t", "always 0", offset, sizeof(uint32_t), "SWR_AltN_0x3064", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(uint32_t);
						write_Coloration_Tag("unk1", "uint32_t", "always 0", offset, sizeof(uint32_t), "SWR_AltN_0x3064", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(uint32_t);

						size_t startoffset_Section3_listOffset = hdr_AltN->offset_Childs + hdr->offset_Section2;
						offset = startoffset_Section3_listOffset;

						uint32_t* listOffsetAltN_Section3 = (uint32_t*)GetOffsetPtr(buf, offset, true);

						for (size_t k = 0; k < hdr_AltN->nb_Childs; k++)
						{
							incSection++;
							incParam = 0;
							
							listOffsetAltN_Section3[k] = val32(listOffsetAltN_Section3[k]);

							write_Coloration_Tag("offset_Section3", "uint32_t", " => 0x" + UnsignedToString(listOffsetAltN_Section3[k] + hdr->offset_Section2, true), startoffset_Section3_listOffset + k * sizeof(uint32_t), sizeof(uint32_t), "SWR_AltN_0x3064", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k);
							
							size_t startoffset_section3 = listOffsetAltN_Section3[k] + hdr->offset_Section2;
							offset = startoffset_section3;

							SWR_MODEL_Section3* section3 = (SWR_MODEL_Section3*)GetOffsetPtr(buf, offset, true);
							section3->offset_section4 = val32(section3->offset_section4);
							section3->offset_section7 = val32(section3->offset_section7);
							section3->nbElementV90 = val16(section3->nbElementV90);
							section3->typeMode = val16(section3->typeMode);
							section3->nbElementV44 = val16(section3->nbElementV44);
							section3->nbElementV52 = val16(section3->nbElementV52);
							section3->offset_V90 = val32(section3->offset_V90);
							section3->offset_unk40 = val32(section3->offset_unk40);
							section3->offset_unk44 = val32(section3->offset_unk44);
							section3->offset_unk48 = val32(section3->offset_unk48);
							section3->offset_unk52 = val32(section3->offset_unk52);
							
							write_Coloration_Tag("offset_section4", "uint32_t", " => "+ UnsignedToString(section3->offset_section4 + hdr->offset_Section2, true), offset, sizeof(uint32_t), "SWR_MODEL_Section3", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint32_t);
							write_Coloration_Tag("offset_section7", "uint32_t", " => " + UnsignedToString(section3->offset_section7 + hdr->offset_Section2, true), offset, sizeof(uint32_t), "SWR_MODEL_Section3", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint32_t);
							write_Coloration_Tag("minX", "float", "also a AABB => So Section3 is a subMesh, or a SubModel", offset, sizeof(float), "SWR_MODEL_Section3", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(float);
							write_Coloration_Tag("minY", "float", "", offset, sizeof(float), "SWR_MODEL_Section3", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(float);
							write_Coloration_Tag("minZ", "float", "", offset, sizeof(float), "SWR_MODEL_Section3", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(float);
							write_Coloration_Tag("maxX", "float", "", offset, sizeof(float), "SWR_MODEL_Section3", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(float);
							write_Coloration_Tag("maxY", "float", "", offset, sizeof(float), "SWR_MODEL_Section3", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(float);
							write_Coloration_Tag("maxZ", "float", "", offset, sizeof(float), "SWR_MODEL_Section3", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(float);
							write_Coloration_Tag("nbElementV90", "uint16_t", "", offset, sizeof(uint16_t), "SWR_MODEL_Section3", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint16_t);
							write_Coloration_Tag("typeMode", "uint16_t", "3 => 3 *float (or uint16); 4 => 4*float (or uint16); 5 (most) => Count for V90", offset, sizeof(uint16_t), "SWR_MODEL_Section3", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint16_t);
							write_Coloration_Tag("offset_V90", "uint32_t", " => " + UnsignedToString(section3->offset_V90 + hdr->offset_Section2, true), offset, sizeof(uint32_t), "SWR_MODEL_Section3", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint32_t);
							write_Coloration_Tag("offset_unk40", "uint32_t", " => " + UnsignedToString(section3->offset_unk40 + hdr->offset_Section2, true), offset, sizeof(uint32_t), "SWR_MODEL_Section3", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint32_t);
							write_Coloration_Tag("offset_unk44", "uint32_t", " => " + UnsignedToString(section3->offset_unk44 + hdr->offset_Section2, true), offset, sizeof(uint32_t), "SWR_MODEL_Section3", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint32_t);
							write_Coloration_Tag("offset_unk48", "uint32_t", " => " + UnsignedToString(section3->offset_unk48 + hdr->offset_Section2, true), offset, sizeof(uint32_t), "SWR_MODEL_Section3", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint32_t);
							write_Coloration_Tag("offset_unk52", "uint32_t", " => " + UnsignedToString(section3->offset_unk52 + hdr->offset_Section2, true), offset, sizeof(uint32_t), "SWR_MODEL_Section3", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint32_t);
							write_Coloration_Tag("nbElementV44", "uint16_t", "", offset, sizeof(uint16_t), "SWR_MODEL_Section3", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint16_t);
							write_Coloration_Tag("nbElementV52", "uint16_t", "", offset, sizeof(uint16_t), "SWR_MODEL_Section3", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint16_t);
							write_Coloration_Tag("unk60", "uint16_t", "always 0.0", offset, sizeof(uint16_t), "SWR_MODEL_Section3", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint16_t);
							write_Coloration_Tag("unk62", "uint16_t", "[0 (most), 0xa] + 0xc 0xe", offset, sizeof(uint16_t), "SWR_MODEL_Section3", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint16_t);


							if ((section3->offset_section4)&&(!checkDuplication(section3->offset_section4 + hdr->offset_Section2, listToAvoidDuplication)))
							{
								listToAvoidDuplication.push_back(section3->offset_section4 + hdr->offset_Section2);

								incSection++;
								incParam = 0;

								size_t startoffset_section4 = section3->offset_section4 + hdr->offset_Section2;
								offset = startoffset_section4;

								SWR_MODEL_Section4* section4 = (SWR_MODEL_Section4*)GetOffsetPtr(buf, offset, true);
								section4->offset_section5 = val32(section4->offset_section5);
								section4->offset_section6 = val32(section4->offset_section6);

								write_Coloration_Tag("unk0", "uint32_t", "could be splitted int uint8 or flags: (second from right) 0(most), 1, 4 or 5. (first from right) 4, 6, 7, 0xc, 0xe, 0xf(most) ", offset, sizeof(uint32_t), "SWR_MODEL_Section4", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint32_t);
								write_Coloration_Tag("unk4", "uint16_t", "always 0", offset, sizeof(uint16_t), "SWR_MODEL_Section4", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint16_t);
								write_Coloration_Tag("unk6", "uint16_t", "always 0", offset, sizeof(uint16_t), "SWR_MODEL_Section4", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint16_t);
								write_Coloration_Tag("offset_section5", "uint32_t", " => " + UnsignedToString(section4->offset_section5 + hdr->offset_Section2, true), offset, sizeof(uint32_t), "SWR_MODEL_Section4", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint32_t);
								write_Coloration_Tag("offset_section6", "uint32_t", " => " + UnsignedToString(section4->offset_section6 + hdr->offset_Section2, true), offset, sizeof(uint32_t), "SWR_MODEL_Section4", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint32_t);


								if ((section4->offset_section5) && (!checkDuplication(section4->offset_section5 + hdr->offset_Section2, listToAvoidDuplication)))
								{
									listToAvoidDuplication.push_back(section4->offset_section5 + hdr->offset_Section2);

									incSection++;
									incParam = 0;
									
									size_t startoffset_section5 = section4->offset_section5 + hdr->offset_Section2;
									offset = startoffset_section5;

									SWR_MODEL_Section5* section5 = (SWR_MODEL_Section5*)GetOffsetPtr(buf, offset, true);

									write_Coloration_Tag("unk0", "uint32_t", "0, 1 (most), 0x41, 0x49", offset, sizeof(uint32_t), "SWR_MODEL_Section5", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint32_t);
									write_Coloration_Tag("unk4", "uint16_t", "look like flags : 0x10, 0x20, 0x40, 0x80, 0xfc, 0x100 (most), 0x128, 0x138, 0x200", offset, sizeof(uint16_t), "SWR_MODEL_Section5", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint16_t);
									write_Coloration_Tag("unk6", "uint16_t", "look like flags : 0x10, 0x20, 0x40, 0x80, 0x8c, 0xb8, 0xbc, 0x100 (most), 0x200", offset, sizeof(uint16_t), "SWR_MODEL_Section5", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint16_t);
									write_Coloration_Tag("unk8_0", "uint16_t", "always 0", offset, sizeof(uint16_t), "SWR_MODEL_Section5", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint16_t);
									write_Coloration_Tag("unk8_1", "uint16_t", "always 0", offset, sizeof(uint16_t), "SWR_MODEL_Section5", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint16_t);
									write_Coloration_Tag("unk12_0", "uint8_t", "0, 2 (most), 4, like flags", offset, sizeof(uint8_t), "SWR_MODEL_Section5", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint8_t);
									write_Coloration_Tag("unk12_1", "uint8_t", "0 (most), 1, 3, like flags", offset, sizeof(uint8_t), "SWR_MODEL_Section5", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint8_t);
									write_Coloration_Tag("unk12_2", "uint8_t", "always 0", offset, sizeof(uint8_t), "SWR_MODEL_Section5", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint8_t);
									write_Coloration_Tag("unk12_3", "uint8_t", "0 (most), 4", offset, sizeof(uint8_t), "SWR_MODEL_Section5", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint8_t);
									write_Coloration_Tag("unk16", "uint16_t", "4, 8, 0x10, 0x20, 0x3f, 0x40 (most), 0x4a, 0x4e, 0x80. look like flgas", offset, sizeof(uint16_t), "SWR_MODEL_Section5", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint16_t);
									write_Coloration_Tag("unk18", "uint16_t", "0x4, 0x8, 0x10, 0x20, 0x23, 0x2e, 0x2f, 0x40 (most), 0x80. look like flags", offset, sizeof(uint16_t), "SWR_MODEL_Section5", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint16_t);
									write_Coloration_Tag("unk20", "uint16_t", "0x800, 0x1000, 0x2000, 0x4000, 0x7e00, 0x8000 (most), 0x9400, 0x9c00. todo splitted uint8", offset, sizeof(uint16_t), "SWR_MODEL_Section5", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint16_t);
									write_Coloration_Tag("unk22", "uint16_t", "0x800, 0x1000, 0x2000, 0x4000, 0x4600, 0x5c00, 0x5e00, 0x8000 (most)", offset, sizeof(uint16_t), "SWR_MODEL_Section5", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint16_t);
									write_Coloration_Tag("unk24", "uint16_t", "0x0, 0x40, 0x80, 0x100, 0x200 (most), 0x2ab, 0x400, 0x800", offset, sizeof(uint16_t), "SWR_MODEL_Section5", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint16_t);
									write_Coloration_Tag("unk26", "uint16_t", "0x7, 0xf, 0x1f, 0x3f, 0x7f, 0xff, 0x16f, 0x1f7, 0x1ff, 0x2aa, 0x365, 0x3ff (most), 0x7ff, 0xd78f", offset, sizeof(uint16_t), "SWR_MODEL_Section5", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint16_t);
									write_Coloration_Tag("offset_Section5_b_0", "uint32_t", " => " + UnsignedToString(val32(section5->offset_Section5_b[0]) + hdr->offset_Section2, true), offset, sizeof(uint32_t), "SWR_MODEL_Section5", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint32_t);
									write_Coloration_Tag("offset_Section5_b_1", "uint32_t", " => " + UnsignedToString(val32(section5->offset_Section5_b[1]) + hdr->offset_Section2, true), offset, sizeof(uint32_t), "SWR_MODEL_Section5", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint32_t);
									write_Coloration_Tag("offset_Section5_b_2", "uint32_t", " => " + UnsignedToString(val32(section5->offset_Section5_b[2]) + hdr->offset_Section2, true), offset, sizeof(uint32_t), "SWR_MODEL_Section5", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint32_t);
									write_Coloration_Tag("offset_Section5_b_3", "uint32_t", " => " + UnsignedToString(val32(section5->offset_Section5_b[3]) + hdr->offset_Section2, true), offset, sizeof(uint32_t), "SWR_MODEL_Section5", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint32_t);
									write_Coloration_Tag("offset_Section5_b_4", "uint32_t", " => " + UnsignedToString(val32(section5->offset_Section5_b[4]) + hdr->offset_Section2, true), offset, sizeof(uint32_t), "SWR_MODEL_Section5", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint32_t);
									write_Coloration_Tag("unk48", "uint32_t", "always 0", offset, sizeof(uint32_t), "SWR_MODEL_Section5", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint32_t);
									write_Coloration_Tag("unk52", "uint32_t", "always 0", offset, sizeof(uint32_t), "SWR_MODEL_Section5", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint32_t);
									write_Coloration_Tag("unk56", "uint8_t", "always 0xa", offset, sizeof(uint8_t), "SWR_MODEL_Section5", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint8_t);
									write_Coloration_Tag("unk57", "uint8_t", "0x0 (most), 0xff", offset, sizeof(uint8_t), "SWR_MODEL_Section5", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint8_t);
									write_Coloration_Tag("unk58", "uint16_t", "many big hole in [1, 0x66f] + 0xffff (None), and 0x23 is most. could be flags because of holes, but I'm thinking of some index, childs in hierarchy could explain the holes may be.", offset, sizeof(uint16_t), "SWR_MODEL_Section5", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint16_t);
									write_Coloration_Tag("unk60", "uint32_t", "always 0", offset, sizeof(uint32_t), "SWR_MODEL_Section5", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint32_t);

									for (size_t m = 0; m < 5; m++)
									{
										if (!section5->offset_Section5_b[m])
											continue;

										if (checkDuplication(val32(section5->offset_Section5_b[m]) + hdr->offset_Section2, listToAvoidDuplication))
											continue;
										listToAvoidDuplication.push_back(val32(section5->offset_Section5_b[m]) + hdr->offset_Section2);

										incSection++;
										incParam = 0;

										size_t startoffset_section5_b = val32(section5->offset_Section5_b[m]) + hdr->offset_Section2;
										offset = startoffset_section5_b;

										SWR_MODEL_Section5_b* section5_b = (SWR_MODEL_Section5_b*)GetOffsetPtr(buf, offset, true);

										write_Coloration_Tag("unk0", "uint16_t", "always 0", offset, sizeof(uint16_t), "SWR_MODEL_Section5_b", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint16_t);
										write_Coloration_Tag("unk2", "uint8_t", "1, 2, 4 (most), 5, 8, 0x10. look like flags", offset, sizeof(uint8_t), "SWR_MODEL_Section5_b", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint8_t);
										write_Coloration_Tag("unk3", "uint8_t", "it's 2 uint4: 0 (most), 1, 2.  and for the second (right) 0(most), 1, 2", offset, sizeof(uint8_t), "SWR_MODEL_Section5_b", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint8_t);
										write_Coloration_Tag("unk4", "uint8_t", "0, 2, 3, 4, 5, 6 (most), 7. look like flags", offset, sizeof(uint8_t), "SWR_MODEL_Section5_b", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint8_t);
										write_Coloration_Tag("unk5", "uint8_t", "0, 2, 3, 4, 5, 6 (most), 7. look like flags", offset, sizeof(uint8_t), "SWR_MODEL_Section5_b", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint8_t);
										write_Coloration_Tag("unk6_a", "uint8_t", "0 (most), 0xfe, or 0xff", offset, sizeof(uint8_t), "SWR_MODEL_Section5_b", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint8_t);
										write_Coloration_Tag("unk6_b", "uint8_t", "0 (most), 0xfe, or 0xff", offset, sizeof(uint8_t), "SWR_MODEL_Section5_b", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint8_t);
										write_Coloration_Tag("unk8", "uint32_t", "always 0", offset, sizeof(uint32_t), "SWR_MODEL_Section5_b", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint32_t);
										write_Coloration_Tag("unk12", "uint16_t", "0xc, 0x1c, 0x3c, 0x7c, 0xfc (most), 0x124, 0x134, 0x1fc. could be splitted as 2 x uint8. look like flags", offset, sizeof(uint16_t), "SWR_MODEL_Section5_b", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint16_t);
										write_Coloration_Tag("unk14", "uint16_t", "0xc, 0x1c, 0x3c, 0x7c, 0x88, 0xb8, 0xfc (most), 0x1fc. could be splitted as 2 x uint8. look like flags", offset, sizeof(uint16_t), "SWR_MODEL_Section5_b", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint16_t);
									}
								}


								if ((section4->offset_section6) && (!checkDuplication(section4->offset_section6 + hdr->offset_Section2, listToAvoidDuplication)))
								{
									listToAvoidDuplication.push_back(section4->offset_section6 + hdr->offset_Section2);
								
									incSection++;
									incParam = 0;
									
									size_t startoffset_section6 = section4->offset_section6 + hdr->offset_Section2;
									offset = startoffset_section6;

									SWR_MODEL_Section6* section6 = (SWR_MODEL_Section6*)GetOffsetPtr(buf, offset, true);

									write_Coloration_Tag("unk0", "uint32_t", "0x0 (second), 0x1 (most), 0x8, 0x9. is flags", offset, sizeof(uint32_t), "SWR_MODEL_Section6", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint32_t);
									write_Coloration_Tag("unk4", "uint16_t", "0x1, 0x2 (most)", offset, sizeof(uint16_t), "SWR_MODEL_Section6", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint16_t);
									write_Coloration_Tag("unk6_0", "uint32_t", "(notice , it's seam few values are inversed on bytes order, Todo check) 4 x unint8: (first left) 1 (most), 2, 3, 4, 6. (second left)  1 or 0x1f (most). (third left) 1, 3, 4 (most), d. (the last) 1 or 0x1f (most).", offset, sizeof(uint32_t), "SWR_MODEL_Section6", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint32_t);
									write_Coloration_Tag("unk6_1", "uint32_t", "4 x unint8: (first left) 1, 2, 3, 4, 6, 7(most). (second left)  1, 3, 7(most). (third left) 0, 1, 3, 4, 7(most). (the last) 1(most), 3, 4 (second), 6, 7.", offset, sizeof(uint32_t), "SWR_MODEL_Section6", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint32_t);
									write_Coloration_Tag("unk14_0", "uint32_t", "(notice , it's seam few values are inversed on bytes order, Todo check) 4 x unint8: (first left) 0(most), 1 , 3, 4. (second left)  0x1f. (third left) 0, 3(most), 4. (the last) 0x1f.", offset, sizeof(uint32_t), "SWR_MODEL_Section6", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint32_t);
									write_Coloration_Tag("unk14_1", "uint32_t", "4 x uint8: 0, 7(most).   7.     3, 4, 7(most).  0(most), 4, 6, 7 ", offset, sizeof(uint32_t), "SWR_MODEL_Section6", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint32_t);
									write_Coloration_Tag("unk22_0", "uint8_t", "always 0", offset, sizeof(uint8_t), "SWR_MODEL_Section6", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint8_t);
									write_Coloration_Tag("unk22_1", "uint8_t", "always 0", offset, sizeof(uint8_t), "SWR_MODEL_Section6", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint8_t);
									write_Coloration_Tag("unk24", "uint32_t", "0xc8000000, 0x00442078, 0x0c080000, 0x0c080001, 0x0c082008. look like flags", offset, sizeof(uint32_t), "SWR_MODEL_Section6", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint32_t);
									write_Coloration_Tag("unk28", "uint32_t", "", offset, sizeof(uint32_t), "SWR_MODEL_Section6", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint32_t);
									write_Coloration_Tag("unk32", "uint16_t", "always 0", offset, sizeof(uint16_t), "SWR_MODEL_Section6", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint16_t);
									write_Coloration_Tag("unk34", "uint16_t", "0 (second), 0xffff (most, None), but after there is progressive hig values, may be offsets.", offset, sizeof(uint16_t), "SWR_MODEL_Section6", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint16_t);
									write_Coloration_Tag("unk36", "uint16_t", "it's 2 x uint8: progressive values  with holes in [0(most) , 0xFF] (could be a index) .     0(most), 1, 0x40, 0xff (look like flags)", offset, sizeof(uint16_t), "SWR_MODEL_Section6", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint16_t);
									write_Coloration_Tag("unk38", "uint16_t", "always 0", offset, sizeof(uint16_t), "SWR_MODEL_Section6", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint16_t);
									write_Coloration_Tag("unk40", "uint32_t", "always 0", offset, sizeof(uint32_t), "SWR_MODEL_Section6", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint32_t);
									write_Coloration_Tag("unk44", "uint32_t", "0 (most), 0x8080, look like flags", offset, sizeof(uint32_t), "SWR_MODEL_Section6", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint32_t);
									write_Coloration_Tag("unk48", "uint32_t", "0 (most), 0x80100000", offset, sizeof(uint32_t), "SWR_MODEL_Section6", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint32_t);
								}
							}



							if (section3->offset_section7)
							{
								incSection++;
								incParam = 0;
								
								size_t startoffset_section7 = section3->offset_section7 + hdr->offset_Section2;
								offset = startoffset_section7;

								SWR_MODEL_Section7* section7 = (SWR_MODEL_Section7*)GetOffsetPtr(buf, offset, true);
								
								write_Coloration_Tag("unk0", "uint16_t", "0(most), 2, 4, 0x10, 0x12, 0x14, 0x20, 0x24. flags", offset, sizeof(uint16_t), "SWR_MODEL_Section7", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint16_t);
								write_Coloration_Tag("unk2_0", "uint8_t", "0 (most), 1, 2, 3, 4, 5, 7, 0xb, 0xc", offset, sizeof(uint8_t), "SWR_MODEL_Section7", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint8_t);
								write_Coloration_Tag("unk2_1", "uint8_t", "", offset, sizeof(uint8_t), "SWR_MODEL_Section7", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint8_t);
								write_Coloration_Tag("unk2_2", "uint8_t", "", offset, sizeof(uint8_t), "SWR_MODEL_Section7", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint8_t);
								write_Coloration_Tag("unk2_3", "uint8_t", "", offset, sizeof(uint8_t), "SWR_MODEL_Section7", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint8_t);
								write_Coloration_Tag("unk6", "uint16_t", "0, 1, 3, 0x3d9, 0x3de, 0x3e1, 0x3e2, 0x3e3, 0x3e4 (most), 0x2838, 0x7200, 0x94b0, 0xd830", offset, sizeof(uint16_t), "SWR_MODEL_Section7", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint16_t);
								write_Coloration_Tag("unk8", "uint16_t", "", offset, sizeof(uint16_t), "SWR_MODEL_Section7", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint16_t);
								write_Coloration_Tag("unk10", "uint16_t", "0(most), 1, 3, 6, 7, 0xb, 0xf, 0x17. flags", offset, sizeof(uint16_t), "SWR_MODEL_Section7", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint16_t);
								write_Coloration_Tag("unk12_0", "uint8_t", "0xff is the most", offset, sizeof(uint8_t), "SWR_MODEL_Section7", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint8_t);
								write_Coloration_Tag("unk12_1", "uint8_t", "0xff is the most", offset, sizeof(uint8_t), "SWR_MODEL_Section7", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint8_t);
								write_Coloration_Tag("unk12_2", "uint8_t", "0xff is the most", offset, sizeof(uint8_t), "SWR_MODEL_Section7", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint8_t);
								write_Coloration_Tag("unk12_3", "uint8_t", "0xff is the most", offset, sizeof(uint8_t), "SWR_MODEL_Section7", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint8_t);
								write_Coloration_Tag("unk12_4", "uint8_t", "0xff is the most", offset, sizeof(uint8_t), "SWR_MODEL_Section7", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint8_t);
								write_Coloration_Tag("unk12_5", "uint8_t", "0xff is the most", offset, sizeof(uint8_t), "SWR_MODEL_Section7", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint8_t);
								write_Coloration_Tag("unk12_6", "uint8_t", "0x3d is the most", offset, sizeof(uint8_t), "SWR_MODEL_Section7", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint8_t);
								write_Coloration_Tag("unk12_7", "uint8_t", "0 is the most", offset, sizeof(uint8_t), "SWR_MODEL_Section7", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint8_t);
								write_Coloration_Tag("unk20", "float", "-14000.0, -5580.0, -4800.0, -3147.0, -2953.0, -2629.0, -1482.0, -329.265991, 0.0 (most), 1.0, 1500.0, 4152.0, 8000.0, 8600.0, 11168.097656, 27813.0", offset, sizeof(float), "SWR_MODEL_Section7", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(float);
								write_Coloration_Tag("unk24", "float", "-12101.0, -9000.0, -3998.197998, -3800.0, -3364.0, 0.0 (most), 1.0, 2.0, 3765.0, 4426.0, 7633.0, 8390.0, 9115.0, 9300.0, 14800.0, 42000.0", offset, sizeof(float), "SWR_MODEL_Section7", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(float);
								write_Coloration_Tag("unk28", "float", "-4712.958008, -3000.0, -1.0 (most), 100.0, 453.0, 557.0, 560.0, 695.0, 891.0, 1273.0, 2800.0, 5934.678223, 6500.0, 21305.0, 30000.0", offset, sizeof(float), "SWR_MODEL_Section7", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(float);
								write_Coloration_Tag("unk32", "float", "-1.0, 0.0 (most), 1.0", offset, sizeof(float), "SWR_MODEL_Section7", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(float);
								write_Coloration_Tag("unk36", "float", "-1.0, 0.0, 1.0 (most)", offset, sizeof(float), "SWR_MODEL_Section7", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(float);
								write_Coloration_Tag("unk40", "uint32_t", "always 0", offset, sizeof(uint32_t), "SWR_MODEL_Section7", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint32_t);
								write_Coloration_Tag("unk44", "uint32_t", "4 x uint8:      0(most), 2.     0(most),1,2.         0(most), 1, 2, 4, 5, 6, 8, 0x10, 0x11, 0x18, 0x20, 0x24, 0x40, 0x80, 0x83, 0x88.      0(most),1,2,4,5,8,0x20, 0x24 0x40, 0x42, 0x48, 0x88,  ", offset, sizeof(uint32_t), "SWR_MODEL_Section7", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint32_t);
								write_Coloration_Tag("unk48", "uint16_t", "0x0 (most), 0x1, 0x100a", offset, sizeof(uint16_t), "SWR_MODEL_Section7", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint16_t);
								write_Coloration_Tag("unk50", "uint16_t", "0x1, 0x2, 0x594c (most), 0xa86c, 0xf280", offset, sizeof(uint16_t), "SWR_MODEL_Section7", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint16_t);
								write_Coloration_Tag("unk52", "uint32_t", "0 the most. look like color RGBA (with lot of alpha at 0)", offset, sizeof(uint32_t), "SWR_MODEL_Section7", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint32_t);
								write_Coloration_Tag("unk56", "uint32_t", "same", offset, sizeof(uint32_t), "SWR_MODEL_Section7", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint32_t);
								write_Coloration_Tag("offset_section8", "uint32_t", " => " + UnsignedToString(section7->offset_section8 + hdr->offset_Section2, true), offset, sizeof(uint32_t), "SWR_MODEL_Section7", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint32_t);

								

								if ((val32(section7->unk52) & 0xFFFF) == 0x6C3C)			//todo test if it's work on all files.
								{
									size_t startoffset_section7_b = offset;

									SWR_MODEL_Section7_b* section7_b = (SWR_MODEL_Section7_b*)GetOffsetPtr(buf, offset, true);

									write_Coloration_Tag("unk0", "uint32_t", "", offset, sizeof(uint32_t), "SWR_MODEL_Section7", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint32_t);
									write_Coloration_Tag("unk1", "uint32_t", "", offset, sizeof(uint32_t), "SWR_MODEL_Section7", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint32_t);
									write_Coloration_Tag("unk2", "uint32_t", "", offset, sizeof(uint32_t), "SWR_MODEL_Section7", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint32_t);
								}


								std::vector<size_t> listOffsetSection8;
								listOffsetSection8.push_back(val32(section7->offset_section8));

								for (size_t m = 0; m < listOffsetSection8.size(); m++)
								{
									if (!listOffsetSection8.at(m))
										continue;
									
									incSection++;
									incParam = 0;

									size_t startoffset_section8 = listOffsetSection8.at(m) + hdr->offset_Section2;
									offset = startoffset_section8;

									SWR_MODEL_Section8* section8 = (SWR_MODEL_Section8*)GetOffsetPtr(buf, offset, true);

									write_Coloration_Tag("unk0_0", "float", "[-9983.669922, 9733.980469]", offset, sizeof(float), "SWR_MODEL_Section8", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(float);
									write_Coloration_Tag("unk0_1", "float", "[-8403.759766, 16209.339844]", offset, sizeof(float), "SWR_MODEL_Section8", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(float);
									write_Coloration_Tag("unk0_2", "float", "[-2920.409912, 1069.109985]", offset, sizeof(float), "SWR_MODEL_Section8", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(float);
									write_Coloration_Tag("unk12_0", "float", "[-1.0, 1.0]", offset, sizeof(float), "SWR_MODEL_Section8", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(float);
									write_Coloration_Tag("unk12_1", "float", "[-1.0, 1.0]", offset, sizeof(float), "SWR_MODEL_Section8", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(float);
									write_Coloration_Tag("unk12_2", "float", "-0.27, -0.05, -0.02, -0.01, 0.0 (most), 0.06, 0.09", offset, sizeof(float), "SWR_MODEL_Section8", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(float);
									write_Coloration_Tag("unk24", "float", "[6.44, 532.820007], 270.350006 is the most", offset, sizeof(float), "SWR_MODEL_Section8", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(float);
									write_Coloration_Tag("unk28", "float", "[6.67,319.540009], 108.32 is the most", offset, sizeof(float), "SWR_MODEL_Section8", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(float);
									write_Coloration_Tag("unk32", "uint32_t", " 0 is the most. could be a offset", offset, sizeof(uint32_t), "SWR_MODEL_Section8", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint32_t);
									write_Coloration_Tag("unk36", "uint16_t", "0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6a, 0x6b, 0x6c, 0xca, 0xcb, 0xd0, 0xd3 (most), 0xd4, 0xd5, 0x12d, 0x130, 0x132, 0x133, 0x134, 0x136, 0x13a, 0x1f5, 0x1f7", offset, sizeof(uint16_t), "SWR_MODEL_Section8", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint16_t);
									write_Coloration_Tag("unk38", "uint16_t", "always 0", offset, sizeof(uint16_t), "SWR_MODEL_Section8", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint16_t);
									write_Coloration_Tag("offset_next_section8", "uint32_t", " => " + UnsignedToString(val32(section8->offset_next_section8) + hdr->offset_Section2, true), offset, sizeof(uint32_t), "SWR_MODEL_Section8", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint32_t);

									listOffsetSection8.push_back(val32(section8->offset_next_section8));
								}
							}



							if (section3->offset_V90)
							{
								incSection++;
								incParam = 0;
								
								size_t startoffset_sectionV90 = section3->offset_V90 + hdr->offset_Section2;
								offset = startoffset_sectionV90;

								uint32_t* listValues = (uint32_t*)GetOffsetPtr(buf, offset, true);

								for (size_t m = 0; m < section3->nbElementV90; m++)
								{
									listValues[m] = val32(listValues[m]);
									write_Coloration_Tag("values", "uint32_t", " may be v90 it's a list of float or uint16_t (so may be float16, todo check) (v44) to group them. Todo to check if number of section mathc with v90 number of group to have properties likes materials, textureDefinitions, (or bone, but I'm not sure there is a bones, may be it's a section)", offset, sizeof(uint32_t), "SWR_MODEL_V90", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, m); offset += sizeof(uint32_t);
								}

							}




							//if ((section3->offset_unk40) && (section3->offset_unk44))			//44 is necessary ?
							if (section3->offset_unk44)
							{
								incSection++;
								incParam = 0;
								
								size_t startoffset_section44 = section3->offset_unk44 + hdr->offset_Section2;
								offset = startoffset_section44;

								SWR_MODEL_Section7* section7 = (SWR_MODEL_Section7*)GetOffsetPtr(buf, offset, true);

								size_t nbElements = 0;
								switch (section3->typeMode)
								{
								case 3: nbElements = 3 * section3->nbElementV44; break;
								//case 4: nbElements = 4 * section3->nbUnk44; break;
								case 4: nbElements = 3 * section3->nbElementV44; break;

								case 5: 
								{
									if (section3->offset_V90)
									{
										uint32_t* listValues = (uint32_t*)GetOffsetPtr(buf, section3->offset_V90 + hdr->offset_Section2, true);
										for (size_t m = 0; m < section3->nbElementV90; m++)
										{
											//nbElements += listValues[m + 2];				// + 2 ?
											nbElements += 3 * listValues[m];
										}
									}
								}
								break;

								default:
									break;
								}


								for (size_t m = 0; m < nbElements; m++)
								{
									if ((false)&& (section3->typeMode == 3))				// only last hole on model 146 and 151 witch have uint32.
									{
										write_Coloration_Tag("values", "float", " no hole into [0(most), 0xffff]. ", offset, sizeof(float), "SWR_MODEL_section44", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, m); offset += sizeof(float);
									}else {
										write_Coloration_Tag("values", "uint16_t", " no hole into [0(most), 0xffff]. ", offset, sizeof(uint16_t), "SWR_MODEL_section44", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, m); offset += sizeof(uint16_t);
									}

								}
							}



							if (section3->offset_unk48)
							{
								incSection++;
								incParam = 0;

								size_t startoffset_section48 = section3->offset_unk48 + hdr->offset_Section2;
								offset = startoffset_section48;

								

								SWR_MODEL_Section48* section48 = (SWR_MODEL_Section48*)GetOffsetPtr(buf, offset, true);

								while (section48->unk0 != 0xDF)
								{
									write_Coloration_Tag("unk0", "uint8_t", "1, 3, 5, 6 (most)", offset, sizeof(uint8_t), "SWR_MODEL_Section48", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(uint8_t);
									write_Coloration_Tag("unk1", "uint8_t", "only paire values in [0(most), 0x3e]", offset, sizeof(uint8_t), "SWR_MODEL_Section48", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(uint8_t);
									write_Coloration_Tag("unk2", "uint8_t", "only paire values in [0(most), 0x3e] + 0x40, 0x50, 0x60, ... 0xf0. it's 2x uint4.", offset, sizeof(uint8_t), "SWR_MODEL_Section48", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(uint8_t);
									write_Coloration_Tag("unk3", "uint8_t", "", offset, sizeof(uint8_t), "SWR_MODEL_Section48", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(uint8_t);
									write_Coloration_Tag("unk4", "uint8_t", "", offset, sizeof(uint8_t), "SWR_MODEL_Section48", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(uint8_t);
									write_Coloration_Tag("unk5", "uint8_t", "", offset, sizeof(uint8_t), "SWR_MODEL_Section48", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(uint8_t);
									write_Coloration_Tag("unk6", "uint8_t", "", offset, sizeof(uint8_t), "SWR_MODEL_Section48", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(uint8_t);
									write_Coloration_Tag("unk7", "uint8_t", "", offset, sizeof(uint8_t), "SWR_MODEL_Section48", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(uint8_t);
									
									section48++;
								}
								write_Coloration_Tag("End", "2 x uint32_t", "", offset, 2 * sizeof(uint32_t), "SWR_MODEL_Section48", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += 2 * sizeof(uint32_t);

							}

							if (section3->offset_unk52)
							{
								incSection++;
								incParam = 0;

								size_t startoffset_section52 = section3->offset_unk52 + hdr->offset_Section2;
								offset = startoffset_section52;

								for (size_t m = 0; m < section3->nbElementV52; m++)
								{
									SWR_MODEL_Section52* section52 = (SWR_MODEL_Section52*)GetOffsetPtr(buf, offset, true);

									write_Coloration_Tag("unk0", "uint16_t", " [0(most), 0xffff] with holes into [0x2000, 0xd000]. if I remember well, there isn't section52 and 44 in the same time.", offset, sizeof(uint16_t), "SWR_MODEL_Section52", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint16_t);
									write_Coloration_Tag("unk2", "uint16_t", "~same unk0", offset, sizeof(uint16_t), "SWR_MODEL_Section52", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint16_t);
									write_Coloration_Tag("unk4", "uint16_t", "~same unk0", offset, sizeof(uint16_t), "SWR_MODEL_Section52", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint16_t);
									write_Coloration_Tag("unk6", "uint16_t", "always 0", offset, sizeof(uint16_t), "SWR_MODEL_Section52", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint16_t);
									write_Coloration_Tag("unk8", "uint8_t", "~same unk0 but 0xff", offset, sizeof(uint8_t), "SWR_MODEL_Section52", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint8_t);
									write_Coloration_Tag("unk9", "uint8_t", "~same unk0 but 0xff", offset, sizeof(uint8_t), "SWR_MODEL_Section52", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint8_t);
									write_Coloration_Tag("unk10", "uint8_t", "~same unk0 but 0xff", offset, sizeof(uint8_t), "SWR_MODEL_Section52", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint8_t);
									write_Coloration_Tag("unk11", "uint8_t", "~same unk0 but 0xff", offset, sizeof(uint8_t), "SWR_MODEL_Section52", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint8_t);
									write_Coloration_Tag("unk12", "uint8_t", "~same unk0 but 0xff", offset, sizeof(uint8_t), "SWR_MODEL_Section52", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint8_t);
									write_Coloration_Tag("unk13", "uint8_t", "~same unk0 but 0xff", offset, sizeof(uint8_t), "SWR_MODEL_Section52", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint8_t);
									write_Coloration_Tag("unk14", "uint8_t", "~same unk0 but 0xff", offset, sizeof(uint8_t), "SWR_MODEL_Section52", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint8_t);
									write_Coloration_Tag("unk15", "uint8_t", "~same unk0 but 0xff. 0xFF most", offset, sizeof(uint8_t), "SWR_MODEL_Section52", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint8_t);
								}
							}

							

						}

					}
					break;

					case 0x5065:
					{
						SWR_AltN_0x5065* section = (SWR_AltN_0x5065*)GetOffsetPtr(buf, offset, true);

						write_Coloration_Tag("unk_0", "uint32_t", "0, 1 or 0xffffffff. => 0 1 -1 ?", offset, sizeof(uint32_t), "SWR_AltN_0x5065", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(uint32_t);
					}
					break;


					case 0x5066:
					{
						SWR_AltN_0x5066* section = (SWR_AltN_0x5066*)GetOffsetPtr(buf, offset, true);

						write_Coloration_Tag("distLod_0", "float", "always 0.0", offset, sizeof(float), "SWR_AltN_0x5066", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(float);
						write_Coloration_Tag("distLod_1", "float", "3.0, 40.0 (most), 2000.0. unk_0 to unk_4 look like LodDistance ranges", offset, sizeof(float), "SWR_AltN_0x5066", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(float);
						write_Coloration_Tag("distLod_2", "float", "40.0, 60.0 (most), 4000.0. ", offset, sizeof(float), "SWR_AltN_0x5066", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(float);
						write_Coloration_Tag("distLod_3", "float", "60.0, 100.0 (most), 6000.0. ", offset, sizeof(float), "SWR_AltN_0x5066", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(float);
						write_Coloration_Tag("distLod_4", "float", "100.0, 120.0, 8000.0, 1000000.0 (most).  ", offset, sizeof(float), "SWR_AltN_0x5066", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(float);
						write_Coloration_Tag("distLod_5", "float", "-1.0 (most) or 1000000.0, ", offset, sizeof(float), "SWR_AltN_0x5066", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(float);
						write_Coloration_Tag("distLod_6", "float", "always -1.0", offset, sizeof(float), "SWR_AltN_0x5066", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(float);
						write_Coloration_Tag("distLod_7", "float", "always -1.0", offset, sizeof(float), "SWR_AltN_0x5066", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(float);

						write_Coloration_Tag("unk_8", "float", "always 0.0", offset, sizeof(float), "SWR_AltN_0x5066", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(float);
						write_Coloration_Tag("unk_9", "float", "always -0.0", offset, sizeof(float), "SWR_AltN_0x5066", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(float);
						write_Coloration_Tag("unk_10", "float", "always 0.0", offset, sizeof(float), "SWR_AltN_0x5066", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(float);
					}
					break;


					case 0xD064:
					{
						SWR_AltN_0xD064* section = (SWR_AltN_0xD064*)GetOffsetPtr(buf, offset, true);

						write_Coloration_Tag("m00", "float", "always 0.0160000008. Matrix3x3 for orientation + scale. apparently Section_0xD064 is a Transform (as D065). Todo Check if there is a direct link with 5066", offset, sizeof(float), "SWR_AltN_0xD064", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(float);
						write_Coloration_Tag("m01", "float", "always 0.0", offset, sizeof(float), "SWR_AltN_0xD064", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(float);
						write_Coloration_Tag("m02", "float", "always 0.0", offset, sizeof(float), "SWR_AltN_0xD064", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(float);

						write_Coloration_Tag("m10", "float", "always 0.0", offset, sizeof(float), "SWR_AltN_0xD064", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(float);
						write_Coloration_Tag("m11", "float", "always 0.0160000008", offset, sizeof(float), "SWR_AltN_0xD064", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(float);
						write_Coloration_Tag("m12", "float", "always 0.0", offset, sizeof(float), "SWR_AltN_0xD064", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(float);
						
						write_Coloration_Tag("m20", "float", "always 0.0", offset, sizeof(float), "SWR_AltN_0xD064", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(float);
						write_Coloration_Tag("m21", "float", "always 0.0", offset, sizeof(float), "SWR_AltN_0xD064", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(float);
						write_Coloration_Tag("m22", "float", "always 0.0160000008", offset, sizeof(float), "SWR_AltN_0xD064", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(float);

						write_Coloration_Tag("posX", "float", "always 0.0", offset, sizeof(float), "SWR_AltN_0xD064", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(float);
						write_Coloration_Tag("posY", "float", "always 0.0", offset, sizeof(float), "SWR_AltN_0xD064", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(float);
						write_Coloration_Tag("posZ", "float", "always 0.0", offset, sizeof(float), "SWR_AltN_0xD064", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(float);
					}
					break;

					case 0xD065:
					{
						SWR_AltN_0xD065* section = (SWR_AltN_0xD065*)GetOffsetPtr(buf, offset, true);

						write_Coloration_Tag("m00", "float", "Matrix3x3 for orientation + scale. apparently Section_0xD065 is a Transform", offset, sizeof(float), "SWR_AltN_0xD065", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(float);
						write_Coloration_Tag("m01", "float", "", offset, sizeof(float), "SWR_AltN_0xD065", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(float);
						write_Coloration_Tag("m02", "float", "", offset, sizeof(float), "SWR_AltN_0xD065", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(float);

						write_Coloration_Tag("m10", "float", "", offset, sizeof(float), "SWR_AltN_0xD065", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(float);
						write_Coloration_Tag("m11", "float", "", offset, sizeof(float), "SWR_AltN_0xD065", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(float);
						write_Coloration_Tag("m12", "float", "", offset, sizeof(float), "SWR_AltN_0xD065", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(float);
						
						write_Coloration_Tag("m20", "float", "", offset, sizeof(float), "SWR_AltN_0xD065", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(float);
						write_Coloration_Tag("m21", "float", "", offset, sizeof(float), "SWR_AltN_0xD065", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(float);
						write_Coloration_Tag("m22", "float", "", offset, sizeof(float), "SWR_AltN_0xD065", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(float);

						write_Coloration_Tag("posX", "float", "", offset, sizeof(float), "SWR_AltN_0xD065", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(float);
						write_Coloration_Tag("posY", "float", "", offset, sizeof(float), "SWR_AltN_0xD065", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(float);
						write_Coloration_Tag("posZ", "float", "", offset, sizeof(float), "SWR_AltN_0xD065", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(float);

						write_Coloration_Tag("unk12_X", "float", "0.0 is the most (it's like D064, else the '5' is for adding this part apparently)", offset, sizeof(float), "SWR_AltN_0xD065", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(float);
						write_Coloration_Tag("unk12_Y", "float", "0.0 is the most", offset, sizeof(float), "SWR_AltN_0xD065", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(float);
						write_Coloration_Tag("unk12_Z", "float", "0.0 is the most", offset, sizeof(float), "SWR_AltN_0xD065", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(float);
					}
					break;

					case 0xD066:
					{
						SWR_AltN_0xD066* section = (SWR_AltN_0xD066*)GetOffsetPtr(buf, offset, true);

						write_Coloration_Tag("unk_0", "uint16_t", "0 (most) or 1", offset, sizeof(uint16_t), "SWR_AltN_0xD066", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(uint16_t);
						write_Coloration_Tag("unk_1", "uint16_t", "0 or 1 (most, exactly always the inverse of unk_1)", offset, sizeof(uint16_t), "SWR_AltN_0xD066", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(uint16_t);

						write_Coloration_Tag("unk_2", "float", "always 0", offset, sizeof(float), "SWR_AltN_0xD066", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(float);
						write_Coloration_Tag("unk_3", "float", "always 0", offset, sizeof(float), "SWR_AltN_0xD066", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(float);
						write_Coloration_Tag("unk_4", "float", "always 1.0", offset, sizeof(float), "SWR_AltN_0xD066", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(float);
					}
					break;

					default:
						break;
				}



				// Recursively parse children if this has any ???
				if ((hdr_AltN->flags & 0x4000)&&(hdr_AltN->offset_Childs))				// 0x5xxx or 0xDxxxx (for 0x3xxx the child are struct_V16)
				{
					size_t startoffset_Child_listOffset = hdr_AltN->offset_Childs + hdr->offset_Section2;
					offset = startoffset_Child_listOffset;

					uint32_t* listOffsetAltN_Child = (uint32_t*)GetOffsetPtr(buf, offset, true);

					for (size_t k = 0; k < hdr_AltN->nb_Childs; k++)
					{
						listOffsetAltN_Child[k] = val32(listOffsetAltN_Child[k]);
						write_Coloration_Tag("offset_Child_SectionAltN", "uint32_t", " => 0x" + UnsignedToString(listRecusiveAltN.back(), true), offset, sizeof(uint32_t), "SWR_AltN_Header", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, k); offset += sizeof(uint32_t);
						
						if (listOffsetAltN_Child[k] == 0)
							continue;

						listRecusiveAltN.push_back(listOffsetAltN_Child[k] + hdr->offset_Section2);						
					}
				}
			}

		}

		



		//-----------------------  Anim :
		
		size_t nbAnim = listPointer_Anim.size();
		for (size_t inc_Anim = 0; inc_Anim < nbAnim; inc_Anim++)
		{
			size_t startSectionAnim = listPointer_Anim.at(inc_Anim);
			offset = startSectionAnim;

			incSection++;
			incParam = 0;

			SWR_Anim_Header* hdr_anim = (SWR_Anim_Header*)GetOffsetPtr(buf, offset, true);
			hdr_anim->nbKeyFrames = val32(hdr_anim->nbKeyFrames);
			hdr_anim->offset_times = val32(hdr_anim->offset_times);
			hdr_anim->offset_values = val32(hdr_anim->offset_values);
			hdr_anim->offset_AltN = val32(hdr_anim->offset_AltN);
			
			write_Coloration_Tag("unk0__0_To_60", "61 x uint32_t", "start of Anim. always 0", offset, 61 * sizeof(uint32_t), "SWR_Anim_Header", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, inc_Anim); offset += 61 * sizeof(uint32_t);
			write_Coloration_Tag("unk1_X", "float", "[0.0333329998, 240.0], 42.1666679 most. SOME the values offset is 0.0333, like if it's a diff time for 30 fps animations", offset, sizeof(float), "SWR_Anim_Header", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, inc_Anim); offset += sizeof(float);
			write_Coloration_Tag("unk1_Y", "float", "always the same value as unk1_X. it's a scale ? ", offset, sizeof(float), "SWR_Anim_Header", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, inc_Anim); offset += sizeof(float);
			write_Coloration_Tag("unk1_Z", "float", "always the same value as unk1_X. it's a scale ? ", offset, sizeof(float), "SWR_Anim_Header", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, inc_Anim); offset += sizeof(float);
			write_Coloration_Tag("unk2", "uint8_t", "always 11.", offset, sizeof(uint8_t), "SWR_Anim_Header", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, inc_Anim); offset += sizeof(uint8_t);
			write_Coloration_Tag("unk3", "uint8_t", "always 0.", offset, sizeof(uint8_t), "SWR_Anim_Header", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, inc_Anim); offset += sizeof(uint8_t);
			write_Coloration_Tag("unk4", "uint8_t", "0 (most), 0x10", offset, sizeof(uint8_t), "SWR_Anim_Header", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, inc_Anim); offset += sizeof(uint8_t);
			write_Coloration_Tag("flags", "uint8_t", " with mask 0x0F, give the number of Components: 1, 0xB or 0xC => 1 component;  4 => 2 comp; 7, 9 or 0xA => 3 comp; 6 or 8 (most) => 4 comp;   5 => strange values instead of offset of values and objects.     0x12 give something strange.   with filter 0xF0, we have 0, 1, 2, or 3(most).", offset, sizeof(uint8_t), "SWR_Anim_Header", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, inc_Anim); offset += sizeof(uint8_t);
			write_Coloration_Tag("nbKeyFrames", "uint32_t", "", offset, sizeof(uint32_t), "SWR_Anim_Header", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, inc_Anim); offset += sizeof(uint32_t);
			write_Coloration_Tag("unk5_X", "float", "[0.0333329998, 240.0], 42.1666679 most. LOTS OF values offset is 0.0333, like if it's a diff time for 30 fps animations", offset, sizeof(float), "SWR_Anim_Header", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, inc_Anim); offset += sizeof(float);
			write_Coloration_Tag("unk5_Y", "float", "always the same value as unk1_X.", offset, sizeof(float), "SWR_Anim_Header", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, inc_Anim); offset += sizeof(float);
			write_Coloration_Tag("unk5_Z", "float", "always 1.0", offset, sizeof(float), "SWR_Anim_Header", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, inc_Anim); offset += sizeof(float);
			write_Coloration_Tag("unk6", "uint32_t", "always 0", offset, sizeof(uint32_t), "SWR_Anim_Header", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, inc_Anim); offset += sizeof(uint32_t);
			write_Coloration_Tag("unk7", "uint32_t", "always 0", offset, sizeof(uint32_t), "SWR_Anim_Header", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, inc_Anim); offset += sizeof(uint32_t);
			write_Coloration_Tag("offset_times", "uint32_t", " => "+ UnsignedToString(hdr_anim->offset_times + hdr->offset_Section2, true), offset, sizeof(uint32_t), "SWR_Anim_Header", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, inc_Anim); offset += sizeof(uint32_t);
			write_Coloration_Tag("offset_values", "uint32_t", " => " + UnsignedToString(hdr_anim->offset_values + hdr->offset_Section2, true), offset, sizeof(uint32_t), "SWR_Anim_Header", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, inc_Anim); offset += sizeof(uint32_t);
			write_Coloration_Tag("offset_AltN", "uint32_t", "target the object at address => " + UnsignedToString(hdr_anim->offset_AltN + hdr->offset_Section2, true), offset, sizeof(uint32_t), "SWR_Anim_Header", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, inc_Anim); offset += sizeof(uint32_t);
			write_Coloration_Tag("unk8", "uint32_t", "1 (most), 4, 5, 6, 0x22, 0x34, 0x3a.", offset, sizeof(uint32_t), "SWR_Anim_Header", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, inc_Anim); offset += sizeof(uint32_t);

			if (hdr_anim->offset_times)
			{
				incSection++;
				incParam = 0;

				size_t startSectionAnim_Times = hdr_anim->offset_times + hdr->offset_Section2;
				offset = startSectionAnim_Times;

				float* values = (float*)GetOffsetPtr(buf, offset, true);
				for (size_t j = 0; j < hdr_anim->nbKeyFrames; j++)
				{
					write_Coloration_Tag("timesValues", "float", "", offset, sizeof(float), "SWR_Anim_Times", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, j); offset += sizeof(float);
				}
			}

			if (hdr_anim->offset_values)
			{
				incSection++;
				incParam = 0;

				size_t startSectionAnim_Values = hdr_anim->offset_values + hdr->offset_Section2;
				offset = startSectionAnim_Values;

				size_t nbComponents = 0;
				switch(hdr_anim->flags & 0x0F)
				{
				case 1: case 0xB: case 0xC:	nbComponents = 1; break;
				case 4:						nbComponents = 2; break;
				case 7: case 9: case 0xA:	nbComponents = 3; break;
				case 6: case 8:				nbComponents = 4; break;

				case 2:								//To anime a Section4, by replacing the Section5 + section5_b
				{
					offset = hdr_anim->offset_AltN + hdr->offset_Section2;
					SWR_Anim_Values_case2_Header* hdr_anim2 = (SWR_Anim_Values_case2_Header*)GetOffsetPtr(buf, offset, true);

					write_Coloration_Tag("offset_section4", "uint32_t", " => "+ UnsignedToString(val32(hdr_anim2->offset_section4) + hdr->offset_Section2, true) , offset, sizeof(uint32_t), "SWR_Anim_Values_case2_Header", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(uint32_t);
					write_Coloration_Tag("unk0", "uint32_t", " always 0 ?", offset, sizeof(uint32_t), "SWR_Anim_Values_case2_Header", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged); offset += sizeof(uint32_t);

					incSection++;
					incParam = 0;

					offset = hdr_anim->offset_values + hdr->offset_Section2;

					uint32_t* listOffset = (uint32_t*)GetOffsetPtr(buf, offset, true);
					for (size_t j = 0; j < hdr_anim->nbKeyFrames; j++)
					{
						write_Coloration_Tag("offset_sectionAnim2", "uint32_t", " => " + UnsignedToString(val32(listOffset[j]) + hdr->offset_Section2, true), offset, sizeof(uint32_t), "SWR_Anim_Values_case2_Header", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, j); offset += sizeof(uint32_t);
					}

					for (size_t j = 0; j < hdr_anim->nbKeyFrames; j++)
					{
						size_t startoffset_section5 = val32(listOffset[j]) + hdr->offset_Section2;
						offset = startoffset_section5;


						//notice: it's possible (specially on the first and last keyframe) that the offset reference to original Section5.
						if (checkDuplication(offset, listToAvoidDuplication))
							continue;
						listToAvoidDuplication.push_back(offset);

						incSection++;
						incParam = 0;


						SWR_MODEL_Section5* section5 = (SWR_MODEL_Section5*)GetOffsetPtr(buf, offset, true);

						write_Coloration_Tag("unk0", "uint32_t", "0, 1 (most), 0x41, 0x49", offset, sizeof(uint32_t), "SWR_MODEL_Section5", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, j); offset += sizeof(uint32_t);
						write_Coloration_Tag("unk4", "uint16_t", "look like flags : 0x10, 0x20, 0x40, 0x80, 0xfc, 0x100 (most), 0x128, 0x138, 0x200", offset, sizeof(uint16_t), "SWR_MODEL_Section5", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, j); offset += sizeof(uint16_t);
						write_Coloration_Tag("unk6", "uint16_t", "look like flags : 0x10, 0x20, 0x40, 0x80, 0x8c, 0xb8, 0xbc, 0x100 (most), 0x200", offset, sizeof(uint16_t), "SWR_MODEL_Section5", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, j); offset += sizeof(uint16_t);
						write_Coloration_Tag("unk8_0", "uint16_t", "always 0", offset, sizeof(uint16_t), "SWR_MODEL_Section5", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, j); offset += sizeof(uint16_t);
						write_Coloration_Tag("unk8_1", "uint16_t", "always 0", offset, sizeof(uint16_t), "SWR_MODEL_Section5", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, j); offset += sizeof(uint16_t);
						write_Coloration_Tag("unk12_0", "uint8_t", "0, 2 (most), 4, like flags", offset, sizeof(uint8_t), "SWR_MODEL_Section5", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, j); offset += sizeof(uint8_t);
						write_Coloration_Tag("unk12_1", "uint8_t", "0 (most), 1, 3, like flags", offset, sizeof(uint8_t), "SWR_MODEL_Section5", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, j); offset += sizeof(uint8_t);
						write_Coloration_Tag("unk12_2", "uint8_t", "always 0", offset, sizeof(uint8_t), "SWR_MODEL_Section5", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, j); offset += sizeof(uint8_t);
						write_Coloration_Tag("unk12_3", "uint8_t", "0 (most), 4", offset, sizeof(uint8_t), "SWR_MODEL_Section5", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, j); offset += sizeof(uint8_t);
						write_Coloration_Tag("unk16", "uint16_t", "4, 8, 0x10, 0x20, 0x3f, 0x40 (most), 0x4a, 0x4e, 0x80. look like flgas", offset, sizeof(uint16_t), "SWR_MODEL_Section5", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, j); offset += sizeof(uint16_t);
						write_Coloration_Tag("unk18", "uint16_t", "0x4, 0x8, 0x10, 0x20, 0x23, 0x2e, 0x2f, 0x40 (most), 0x80. look like flags", offset, sizeof(uint16_t), "SWR_MODEL_Section5", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, j); offset += sizeof(uint16_t);
						write_Coloration_Tag("unk20", "uint16_t", "0x800, 0x1000, 0x2000, 0x4000, 0x7e00, 0x8000 (most), 0x9400, 0x9c00. todo splitted uint8", offset, sizeof(uint16_t), "SWR_MODEL_Section5", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, j); offset += sizeof(uint16_t);
						write_Coloration_Tag("unk22", "uint16_t", "0x800, 0x1000, 0x2000, 0x4000, 0x4600, 0x5c00, 0x5e00, 0x8000 (most)", offset, sizeof(uint16_t), "SWR_MODEL_Section5", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, j); offset += sizeof(uint16_t);
						write_Coloration_Tag("unk24", "uint16_t", "0x0, 0x40, 0x80, 0x100, 0x200 (most), 0x2ab, 0x400, 0x800", offset, sizeof(uint16_t), "SWR_MODEL_Section5", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, j); offset += sizeof(uint16_t);
						write_Coloration_Tag("unk26", "uint16_t", "0x7, 0xf, 0x1f, 0x3f, 0x7f, 0xff, 0x16f, 0x1f7, 0x1ff, 0x2aa, 0x365, 0x3ff (most), 0x7ff, 0xd78f", offset, sizeof(uint16_t), "SWR_MODEL_Section5", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, j); offset += sizeof(uint16_t);
						write_Coloration_Tag("offset_Section5_b_0", "uint32_t", " => " + UnsignedToString(val32(section5->offset_Section5_b[0]) + hdr->offset_Section2, true), offset, sizeof(uint32_t), "SWR_MODEL_Section5", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, j); offset += sizeof(uint32_t);
						write_Coloration_Tag("offset_Section5_b_1", "uint32_t", " => " + UnsignedToString(val32(section5->offset_Section5_b[1]) + hdr->offset_Section2, true), offset, sizeof(uint32_t), "SWR_MODEL_Section5", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, j); offset += sizeof(uint32_t);
						write_Coloration_Tag("offset_Section5_b_2", "uint32_t", " => " + UnsignedToString(val32(section5->offset_Section5_b[2]) + hdr->offset_Section2, true), offset, sizeof(uint32_t), "SWR_MODEL_Section5", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, j); offset += sizeof(uint32_t);
						write_Coloration_Tag("offset_Section5_b_3", "uint32_t", " => " + UnsignedToString(val32(section5->offset_Section5_b[3]) + hdr->offset_Section2, true), offset, sizeof(uint32_t), "SWR_MODEL_Section5", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, j); offset += sizeof(uint32_t);
						write_Coloration_Tag("offset_Section5_b_4", "uint32_t", " => " + UnsignedToString(val32(section5->offset_Section5_b[4]) + hdr->offset_Section2, true), offset, sizeof(uint32_t), "SWR_MODEL_Section5", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, j); offset += sizeof(uint32_t);
						write_Coloration_Tag("unk48", "uint32_t", "always 0", offset, sizeof(uint32_t), "SWR_MODEL_Section5", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, j); offset += sizeof(uint32_t);
						write_Coloration_Tag("unk52", "uint32_t", "always 0", offset, sizeof(uint32_t), "SWR_MODEL_Section5", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, j); offset += sizeof(uint32_t);
						write_Coloration_Tag("unk56", "uint8_t", "always 0xa => with unk57 and unk58, could be texture ref", offset, sizeof(uint8_t), "SWR_MODEL_Section5", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, j); offset += sizeof(uint8_t);
						write_Coloration_Tag("unk57", "uint8_t", "0x0 (most), 0xff => with unk56 and unk58, could be texture ref", offset, sizeof(uint8_t), "SWR_MODEL_Section5", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, j); offset += sizeof(uint8_t);
						write_Coloration_Tag("unk58", "uint16_t", "many big hole in [1, 0x66f] + 0xffff (None), and 0x23 is most. could be flags because of holes, but I'm thinking of some index, childs in hierarchy could explain the holes may be.", offset, sizeof(uint16_t), "SWR_MODEL_Section5", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, j); offset += sizeof(uint16_t);
						write_Coloration_Tag("unk60", "uint32_t", "always 0", offset, sizeof(uint32_t), "SWR_MODEL_Section5", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, j); offset += sizeof(uint32_t);

						for (size_t m = 0; m < 5; m++)
						{
							if (!section5->offset_Section5_b[m])
								continue;

							if (checkDuplication(val32(section5->offset_Section5_b[m]) + hdr->offset_Section2, listToAvoidDuplication))
								continue;

							listToAvoidDuplication.push_back(val32(section5->offset_Section5_b[m]) + hdr->offset_Section2);

							incSection++;
							incParam = 0;

							size_t startoffset_section5_b = val32(section5->offset_Section5_b[m]) + hdr->offset_Section2;
							offset = startoffset_section5_b;

							SWR_MODEL_Section5_b* section5_b = (SWR_MODEL_Section5_b*)GetOffsetPtr(buf, offset, true);

							write_Coloration_Tag("unk0", "uint16_t", "always 0", offset, sizeof(uint16_t), "SWR_MODEL_Section5_b", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, j); offset += sizeof(uint16_t);
							write_Coloration_Tag("unk2", "uint8_t", "1, 2, 4 (most), 5, 8, 0x10. look like flags", offset, sizeof(uint8_t), "SWR_MODEL_Section5_b", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, j); offset += sizeof(uint8_t);
							write_Coloration_Tag("unk3", "uint8_t", "it's 2 uint4: 0 (most), 1, 2.  and for the second (right) 0(most), 1, 2", offset, sizeof(uint8_t), "SWR_MODEL_Section5_b", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, j); offset += sizeof(uint8_t);
							write_Coloration_Tag("unk4", "uint8_t", "0, 2, 3, 4, 5, 6 (most), 7. look like flags", offset, sizeof(uint8_t), "SWR_MODEL_Section5_b", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, j); offset += sizeof(uint8_t);
							write_Coloration_Tag("unk5", "uint8_t", "0, 2, 3, 4, 5, 6 (most), 7. look like flags", offset, sizeof(uint8_t), "SWR_MODEL_Section5_b", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, j); offset += sizeof(uint8_t);
							write_Coloration_Tag("unk6_a", "uint8_t", "0 (most), 0xfe, or 0xff", offset, sizeof(uint8_t), "SWR_MODEL_Section5_b", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, j); offset += sizeof(uint8_t);
							write_Coloration_Tag("unk6_b", "uint8_t", "0 (most), 0xfe, or 0xff", offset, sizeof(uint8_t), "SWR_MODEL_Section5_b", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, j); offset += sizeof(uint8_t);
							write_Coloration_Tag("unk8", "uint32_t", "always 0", offset, sizeof(uint32_t), "SWR_MODEL_Section5_b", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, j); offset += sizeof(uint32_t);
							write_Coloration_Tag("unk12", "uint16_t", "0xc, 0x1c, 0x3c, 0x7c, 0xfc (most), 0x124, 0x134, 0x1fc. could be splitted as 2 x uint8. look like flags", offset, sizeof(uint16_t), "SWR_MODEL_Section5_b", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, j); offset += sizeof(uint16_t);
							write_Coloration_Tag("unk14", "uint16_t", "0xc, 0x1c, 0x3c, 0x7c, 0x88, 0xb8, 0xfc (most), 0x1fc. could be splitted as 2 x uint8. look like flags", offset, sizeof(uint16_t), "SWR_MODEL_Section5_b", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, j); offset += sizeof(uint16_t);
						}
					}
				}

				case 5:
				{
					//I think the case 5 use splines animations : offset_values and offset_AltN may be are offset for the spline. Todo check

					::printf("Anim flag 5 (nbKf: %d) offset for spline ? offVal : %s, offAlt: %s. skipped.\n", hdr_anim->nbKeyFrames, UnsignedToString(hdr_anim->offset_values, true).c_str(), UnsignedToString(hdr_anim->offset_AltN, true).c_str());
					notifyWarning();

				}break;

				default:
				{
					::printf("Warning: Unknowed animation flags for component %s. skipped.\n", UnsignedToString(hdr_anim->flags, true).c_str());
					notifyWarning();
				}break;
				}



				if (nbComponents != 0)
				{
					float* values = (float*)GetOffsetPtr(buf, offset, true);
					for (size_t j = 0; j < hdr_anim->nbKeyFrames; j++)
					{
						if (nbComponents != 4)
						{
							write_Coloration_Tag(string("Value") + ((nbComponents != 1) ? "_X" : ""), "float", "", offset, sizeof(float), "SWR_Anim_Values", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, j); offset += sizeof(float);
							if (nbComponents > 1)
							{
								write_Coloration_Tag("Value_Y", "float", "", offset, sizeof(float), "SWR_Anim_Values", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, j); offset += sizeof(float);
							}
							if (nbComponents > 2)
							{
								write_Coloration_Tag("Value_Z", "float", "", offset, sizeof(float), "SWR_Anim_Values", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, j); offset += sizeof(float);
							}

						}
						else {			//apparently it's quaternion, and the order is W XYZ, to be simple ...
							write_Coloration_Tag("Value_W", "float", "", offset, sizeof(float), "SWR_Anim_Values", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, j); offset += sizeof(float);
							write_Coloration_Tag("Value_X", "float", "", offset, sizeof(float), "SWR_Anim_Values", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, j); offset += sizeof(float);
							write_Coloration_Tag("Value_Y", "float", "", offset, sizeof(float), "SWR_Anim_Values", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, j); offset += sizeof(float);
							write_Coloration_Tag("Value_Z", "float", "", offset, sizeof(float), "SWR_Anim_Values", parent, idTag++, incSection, incParam++, listBytesAllreadyTagged, j); offset += sizeof(float);
						}
					}
				}
			}
		}



	}

	write_Coloration_Tag("Offset_EndOfFile", "uint32_t", " to have Section2 size of the last Model.", startoffsetModelHeader + nbModels * sizeof(SWR_MODELHeader), sizeof(uint32_t), "SWR_MODELHeader", parent, idTag++, 0, 0, listBytesAllreadyTagged);



	write_Coloration_Gaps(0x0, (size_t)-1,  sizeof(uint32_t) + sizeof(uint16_t), idTag, "Empty", parent, listBytesAllreadyTagged);		//test Empty/gaps/holes.
}





/*-------------------------------------------------------------------------------\
|                             write_Coloration_Tag			                     |
\-------------------------------------------------------------------------------*/
void Swr_Model::write_Coloration_Tag(string paramName, string paramType, string paramComment, size_t startOffset, size_t size, string sectionName, TiXmlElement* parent, size_t idTag, size_t sectionIndex, size_t paramIndex, std::vector<size_t> &listBytesAllreadyTagged, size_t sectionIndexInList, bool checkAllreadyTaggued)
{
	TiXmlElement* tag_node = new TiXmlElement("TAG");

	tag_node->SetAttribute("id", UnsignedToString(idTag, false));


	TiXmlElement* start_offset_node = new TiXmlElement("start_offset");
	TiXmlText* text = new TiXmlText(std::to_string(startOffset));
	start_offset_node->LinkEndChild(text);
	tag_node->LinkEndChild(start_offset_node);

	TiXmlElement* end_offset_node = new TiXmlElement("end_offset");
	text = new TiXmlText(std::to_string(startOffset + size - 1));
	end_offset_node->LinkEndChild(text);
	tag_node->LinkEndChild(end_offset_node);

	TiXmlElement* text_node = new TiXmlElement("tag_text");
	text = new TiXmlText(sectionName + ((sectionIndexInList != (size_t)-1) ? "[" + std::to_string(sectionIndexInList) + "]" : "") + "." + paramName + " (" + paramType + ") : " + paramComment);
	text_node->LinkEndChild(text);
	tag_node->LinkEndChild(text_node);





	if (listTagColors.size() == 0)
	{
		listTagColors.push_back(std::vector<std::vector<string>>());
		listTagColors.back().push_back(std::vector<string>());
		listTagColors.back().back().push_back("#000000");			//background color
		listTagColors.back().back().push_back("#FFFFFF");			//font color (just to possibility read from background color)
	}

	size_t sectionIndex_tmp = sectionIndex % listTagColors.size();
	std::vector<std::vector<string>> &sectionColorlist = listTagColors.at(sectionIndex_tmp);
	size_t paramIndex_tmp = paramIndex % sectionColorlist.size();
	std::vector<string> &paramColors = sectionColorlist.at(paramIndex_tmp);

	TiXmlElement* font_colour_node = new TiXmlElement("font_colour");
	text = new TiXmlText(paramColors.at(1));
	font_colour_node->LinkEndChild(text);
	tag_node->LinkEndChild(font_colour_node);

	TiXmlElement* bg_colour_node = new TiXmlElement("note_colour");
	text = new TiXmlText(paramColors.at(0));
	bg_colour_node->LinkEndChild(text);
	tag_node->LinkEndChild(bg_colour_node);

	parent->LinkEndChild(tag_node);




	//un check d'overide , pour savoir si des blocks se chevauche.
	size_t index;
	size_t limit = listBytesAllreadyTagged.size();
	for (size_t i = 0; i < size; i++)
	{
		index = startOffset + i;
		if (index >= limit)
		{
			::printf("Error on tagID %i : overflow %s >= %s.\n", idTag, UnsignedToString(index, true).c_str(), UnsignedToString(limit, true).c_str());
			notifyError();
			throw("overflow");
			continue;
		}

		if ((checkAllreadyTaggued) && (listBytesAllreadyTagged.at(index)!=-1))
		{
			::printf("warning on tagID %i : the byte %s allready taggued, may be a overflow between blocks (tag: %i). Infos : %s. \n", idTag, UnsignedToString(index, true).c_str(), listBytesAllreadyTagged.at(index), (sectionName + ((sectionIndexInList != (size_t)-1) ? "[" + std::to_string(sectionIndexInList) + "]" : "") + "." + paramName + " (" + paramType + ") : " + paramComment).c_str());
			notifyError();
			throw("overide Byte");
		}

		listBytesAllreadyTagged.at(index) = idTag;
	}
}




/*-------------------------------------------------------------------------------\
|                             write_Coloration_Gaps			                     |
\-------------------------------------------------------------------------------*/
void Swr_Model::write_Coloration_Gaps(size_t startOffsetToConsidere, size_t endOffsetToConsidere, size_t sizeFilter, size_t start_idTag, string sectionName, TiXmlElement* parent, std::vector<size_t> &listBytesAllreadyTagged)
{
	size_t nbBytes = listBytesAllreadyTagged.size();
	if ((nbBytes == 0) || (startOffsetToConsidere >= nbBytes) || (startOffsetToConsidere > endOffsetToConsidere))
		return;

	if (endOffsetToConsidere >= nbBytes)
		endOffsetToConsidere = nbBytes - 1;


	size_t sectionStart = (size_t)-1;
	size_t inc = 0;
	bool isByteTagged = false;
	for (size_t i = startOffsetToConsidere; i <= endOffsetToConsidere; i++)			//detection of the Hole
	{
		isByteTagged = listBytesAllreadyTagged.at(i) != (size_t)-1;

		if ((!isByteTagged) && (sectionStart == (size_t)-1))
		{
			sectionStart = i;

		}else if (((isByteTagged) || (i == endOffsetToConsidere)) && (sectionStart != (size_t)-1)) {		//if end of Section, or end of range.

			size_t size = i - sectionStart;

			if (size > sizeFilter)
			{
				TiXmlElement* tag_node = new TiXmlElement("TAG");

				tag_node->SetAttribute("id", UnsignedToString(start_idTag++, false));


				TiXmlElement* start_offset_node = new TiXmlElement("start_offset");
				TiXmlText* text = new TiXmlText(std::to_string(sectionStart));
				start_offset_node->LinkEndChild(text);
				tag_node->LinkEndChild(start_offset_node);

				start_offset_node = new TiXmlElement("start_offset_Hexa");
				text = new TiXmlText(UnsignedToString(sectionStart, true));
				start_offset_node->LinkEndChild(text);
				tag_node->LinkEndChild(start_offset_node);

				TiXmlElement* end_offset_node = new TiXmlElement("end_offset");
				text = new TiXmlText(std::to_string(sectionStart + size - 1));
				end_offset_node->LinkEndChild(text);
				tag_node->LinkEndChild(end_offset_node);

				TiXmlElement* text_node = new TiXmlElement("tag_text");
				text = new TiXmlText(sectionName + "[" + std::to_string(inc++) + "]. Size=" + std::to_string(size));
				text_node->LinkEndChild(text);
				tag_node->LinkEndChild(text_node);

				TiXmlElement* font_colour_node = new TiXmlElement("font_colour");
				text = new TiXmlText("#000000");
				font_colour_node->LinkEndChild(text);
				tag_node->LinkEndChild(font_colour_node);

				TiXmlElement* bg_colour_node = new TiXmlElement("note_colour");
				text = new TiXmlText("#FF0000");
				bg_colour_node->LinkEndChild(text);
				tag_node->LinkEndChild(bg_colour_node);

				parent->LinkEndChild(tag_node);
			}

			sectionStart = (size_t)-1;
		}
	}
}

/*-------------------------------------------------------------------------------\
|                             checkDuplication				                     |
\-------------------------------------------------------------------------------*/
bool Swr_Model::checkDuplication(size_t offset, std::vector<size_t> &listToAvoidDuplication)
{
	size_t nbElement = listToAvoidDuplication.size();
	for (size_t i = 0; i < nbElement; i++)
		if (listToAvoidDuplication.at(i) == offset)
			return true;
	return false;
};
