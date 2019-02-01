package com.sanguo.game.server.connectlogic.common.message.ProtoMartialClub
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class ProtoCSDelParttimerReq
	{
		public static const PROTO:String = "ProtoMartialClub.ProtoCSDelParttimerReq";
		public var package_root:*;
		public  var message:*;
		public var myUid:int;
		public var detachUid:int;
		public var grade:int;
		public var slot:int;
		public var heroId:int;
		public function ProtoCSDelParttimerReq(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			myUid = undefined;
			detachUid = undefined;
			grade = undefined;
			slot = undefined;
			heroId = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.myUid = this.myUid;
			serializeObj.detachUid = this.detachUid;
			serializeObj.grade = this.grade;
			serializeObj.slot = this.slot;
			serializeObj.heroId = this.heroId;
			return serializeObj;
		}
		public function unserialize(msgObj:*):ProtoCSDelParttimerReq
		{
			myUid = undefined;
			detachUid = undefined;
			grade = undefined;
			slot = undefined;
			heroId = undefined;
			this.myUid = msgObj.myUid;
			this.detachUid = msgObj.detachUid;
			this.grade = msgObj.grade;
			this.slot = msgObj.slot;
			this.heroId = msgObj.heroId;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ProtoCSDelParttimerReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}