package com.sanguo.game.server.connectlogic.common.message.ProtoAlliance
{
	import laya.utils.Byte;
	public class RequestAllianceFunctionBC
	{
		public static const PROTO:String = "ProtoAlliance.RequestAllianceFunctionBC";
		public var package_root:*;
		public  var message:*;
		public var aid:int;
		public var uid:int;
		public var type:int;
		public function RequestAllianceFunctionBC(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			aid = undefined;
			uid = undefined;
			type = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.aid = this.aid;
			serializeObj.uid = this.uid;
			serializeObj.type = this.type;
			return serializeObj;
		}
		public function unserialize(msgObj:*):RequestAllianceFunctionBC
		{
			aid = undefined;
			uid = undefined;
			type = undefined;
			this.aid = msgObj.aid;
			this.uid = msgObj.uid;
			this.type = msgObj.type;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):RequestAllianceFunctionBC
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}