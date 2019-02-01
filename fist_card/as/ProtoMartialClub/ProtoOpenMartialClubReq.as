package com.sanguo.game.server.connectlogic.common.message.ProtoMartialClub
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class ProtoOpenMartialClubReq
	{
		public static const PROTO:String = "ProtoMartialClub.ProtoOpenMartialClubReq";
		public var package_root:*;
		public  var message:*;
		public var grade:int;
		public function ProtoOpenMartialClubReq(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			grade = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.grade = this.grade;
			return serializeObj;
		}
		public function unserialize(msgObj:*):ProtoOpenMartialClubReq
		{
			grade = undefined;
			this.grade = msgObj.grade;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ProtoOpenMartialClubReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}