package com.sanguo.game.server.connectlogic.common.message.ProtoNPCCustomer
{
	import laya.utils.Byte;
	public class SellPropsResp
	{
		public static const PROTO:String = "ProtoNPCCustomer.SellPropsResp";
		public var package_root:*;
		public  var message:*;
		public var commons:CommonItemsCPP;
		public var ts:int;
		public var npcid:int;
		public function SellPropsResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			commons = undefined;
			ts = undefined;
			npcid = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			if(this.commons!= undefined)
			{
				serializeObj.commons = this.commons.serialize();
			}
			serializeObj.ts = this.ts;
			serializeObj.npcid = this.npcid;
			return serializeObj;
		}
		public function unserialize(msgObj:*):SellPropsResp
		{
			commons = undefined;
			ts = undefined;
			npcid = undefined;
			if(msgObj.hasOwnProperty("commons"))
			{
				this.commons = new CommonItemsCPP(package_root).unserialize(msgObj.commons);
			}
			this.ts = msgObj.ts;
			this.npcid = msgObj.npcid;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):SellPropsResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}