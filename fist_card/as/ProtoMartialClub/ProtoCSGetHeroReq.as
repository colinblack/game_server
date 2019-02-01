package com.sanguo.game.server.connectlogic.common.message.ProtoMartialClub
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class ProtoCSGetHeroReq
	{
		public static const PROTO:String = "ProtoMartialClub.ProtoCSGetHeroReq";
		public var package_root:*;
		public  var message:*;
		public var myUid:int;
		public var ownerUid:int;
		public var grade:int;
		public function ProtoCSGetHeroReq(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			myUid = undefined;
			ownerUid = undefined;
			grade = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.myUid = this.myUid;
			serializeObj.ownerUid = this.ownerUid;
			serializeObj.grade = this.grade;
			return serializeObj;
		}
		public function unserialize(msgObj:*):ProtoCSGetHeroReq
		{
			myUid = undefined;
			ownerUid = undefined;
			grade = undefined;
			this.myUid = msgObj.myUid;
			this.ownerUid = msgObj.ownerUid;
			this.grade = msgObj.grade;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ProtoCSGetHeroReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}