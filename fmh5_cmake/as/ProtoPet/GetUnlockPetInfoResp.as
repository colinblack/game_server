package com.sanguo.game.server.connectlogic.common.message.ProtoPet
{
	import laya.utils.Byte;
	public class GetUnlockPetInfoResp
	{
		public static const PROTO:String = "ProtoPet.GetUnlockPetInfoResp";
		public var package_root:*;
		public  var message:*;
		public var arrayPet:Vector.<UnlockPetCPP>;
		public function GetUnlockPetInfoResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			arrayPet = new Vector.<UnlockPetCPP>();
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.arrayPet = [];
			for(var i:int = 0;i < this.arrayPet.length;i++)
			{
				serializeObj.arrayPet.push(this.arrayPet[i].serialize());
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):GetUnlockPetInfoResp
		{
			arrayPet = new Vector.<UnlockPetCPP>();
			for(var i:int = 0;i < msgObj.arrayPet.length;i++)
			{
				this.arrayPet.push(new UnlockPetCPP(package_root).unserialize(msgObj.arrayPet[i]));
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):GetUnlockPetInfoResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}