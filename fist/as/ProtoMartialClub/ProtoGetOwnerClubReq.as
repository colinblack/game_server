package com.sanguo.game.server.connectlogic.common.message.ProtoMartialClub
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class ProtoGetOwnerClubReq
	{
		public static const PROTO:String = "ProtoMartialClub.ProtoGetOwnerClubReq";
		public var package_root:*;
		public  var message:*;
		public var grade:int;
		public function ProtoGetOwnerClubReq(root:*)
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
		public function unserialize(msgObj:*):ProtoGetOwnerClubReq
		{
			grade = undefined;
			this.grade = msgObj.grade;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ProtoGetOwnerClubReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}