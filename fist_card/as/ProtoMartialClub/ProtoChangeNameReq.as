package com.sanguo.game.server.connectlogic.common.message.ProtoMartialClub
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class ProtoChangeNameReq
	{
		public static const PROTO:String = "ProtoMartialClub.ProtoChangeNameReq";
		public var package_root:*;
		public  var message:*;
		public var grade:int;
		public var name:String;
		public function ProtoChangeNameReq(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			grade = undefined;
			name = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.grade = this.grade;
			serializeObj.name = this.name;
			return serializeObj;
		}
		public function unserialize(msgObj:*):ProtoChangeNameReq
		{
			grade = undefined;
			name = undefined;
			this.grade = msgObj.grade;
			this.name = msgObj.name;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ProtoChangeNameReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}