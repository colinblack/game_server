package com.sanguo.game.server.connectlogic.common.message.ProtoNPCUser
{
	import laya.utils.Byte;
	public class OthProduceCPP
	{
		public static const PROTO:String = "ProtoNPCUser.OthProduceCPP";
		public var package_root:*;
		public  var message:*;
		public var ud:int;
		public var status:int;
		public function OthProduceCPP(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			ud = undefined;
			status = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.ud = this.ud;
			serializeObj.status = this.status;
			return serializeObj;
		}
		public function unserialize(msgObj:*):OthProduceCPP
		{
			ud = undefined;
			status = undefined;
			this.ud = msgObj.ud;
			this.status = msgObj.status;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):OthProduceCPP
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}