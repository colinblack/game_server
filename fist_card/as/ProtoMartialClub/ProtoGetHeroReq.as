package com.sanguo.game.server.connectlogic.common.message.ProtoMartialClub
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class ProtoGetHeroReq
	{
		public static const PROTO:String = "ProtoMartialClub.ProtoGetHeroReq";
		public var package_root:*;
		public  var message:*;
		public var ownerUid:int;
		public var grade:int;
		public function ProtoGetHeroReq(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			ownerUid = undefined;
			grade = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.ownerUid = this.ownerUid;
			serializeObj.grade = this.grade;
			return serializeObj;
		}
		public function unserialize(msgObj:*):ProtoGetHeroReq
		{
			ownerUid = undefined;
			grade = undefined;
			this.ownerUid = msgObj.ownerUid;
			this.grade = msgObj.grade;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ProtoGetHeroReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}