package com.sanguo.game.server.connectlogic.common.message.ProtoAlliance
{
	import laya.utils.Byte;
	public class RequestAddMemberHelpTimesBC
	{
		public static const PROTO:String = "ProtoAlliance.RequestAddMemberHelpTimesBC";
		public var package_root:*;
		public  var message:*;
		public var aid:int;
		public var uid:int;
		public function RequestAddMemberHelpTimesBC(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			aid = undefined;
			uid = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.aid = this.aid;
			serializeObj.uid = this.uid;
			return serializeObj;
		}
		public function unserialize(msgObj:*):RequestAddMemberHelpTimesBC
		{
			aid = undefined;
			uid = undefined;
			this.aid = msgObj.aid;
			this.uid = msgObj.uid;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):RequestAddMemberHelpTimesBC
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}