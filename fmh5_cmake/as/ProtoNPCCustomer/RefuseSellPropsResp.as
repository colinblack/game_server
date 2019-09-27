package com.sanguo.game.server.connectlogic.common.message.ProtoNPCCustomer
{
	import laya.utils.Byte;
	public class RefuseSellPropsResp
	{
		public static const PROTO:String = "ProtoNPCCustomer.RefuseSellPropsResp";
		public var package_root:*;
		public  var message:*;
		public var ts:int;
		public var npcid:int;
		public function RefuseSellPropsResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			ts = undefined;
			npcid = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.ts = this.ts;
			serializeObj.npcid = this.npcid;
			return serializeObj;
		}
		public function unserialize(msgObj:*):RefuseSellPropsResp
		{
			ts = undefined;
			npcid = undefined;
			this.ts = msgObj.ts;
			this.npcid = msgObj.npcid;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):RefuseSellPropsResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}