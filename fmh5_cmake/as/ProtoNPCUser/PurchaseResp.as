package com.sanguo.game.server.connectlogic.common.message.ProtoNPCUser
{
	import laya.utils.Byte;
	public class PurchaseResp
	{
		public static const PROTO:String = "ProtoNPCUser.PurchaseResp";
		public var package_root:*;
		public  var message:*;
		public var commons:CommonItemsCPP;
		public var npcshop:NPCShopCPP;
		public function PurchaseResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			commons = undefined;
			npcshop = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.commons = this.commons.serialize();
			serializeObj.npcshop = this.npcshop.serialize();
			return serializeObj;
		}
		public function unserialize(msgObj:*):PurchaseResp
		{
			commons = undefined;
			npcshop = undefined;
			this.commons = new CommonItemsCPP(package_root).unserialize(msgObj.commons);
			this.npcshop = new NPCShopCPP(package_root).unserialize(msgObj.npcshop);
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):PurchaseResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}