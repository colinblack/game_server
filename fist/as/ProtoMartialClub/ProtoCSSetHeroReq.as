package com.sanguo.game.server.connectlogic.common.message.ProtoMartialClub
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class ProtoCSSetHeroReq
	{
		public static const PROTO:String = "ProtoMartialClub.ProtoCSSetHeroReq";
		public var package_root:*;
		public  var message:*;
		public var myUid:int;
		public var detachUid:int;
		public var grade:int;
		public var slot:int;
		public var setHero:MartialHeroInfo;
		public function ProtoCSSetHeroReq(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			myUid = undefined;
			detachUid = undefined;
			grade = undefined;
			slot = undefined;
			setHero = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.myUid = this.myUid;
			serializeObj.detachUid = this.detachUid;
			serializeObj.grade = this.grade;
			serializeObj.slot = this.slot;
			serializeObj.setHero = this.setHero.serialize();
			return serializeObj;
		}
		public function unserialize(msgObj:*):ProtoCSSetHeroReq
		{
			myUid = undefined;
			detachUid = undefined;
			grade = undefined;
			slot = undefined;
			setHero = undefined;
			this.myUid = msgObj.myUid;
			this.detachUid = msgObj.detachUid;
			this.grade = msgObj.grade;
			this.slot = msgObj.slot;
			this.setHero = new MartialHeroInfo(package_root).unserialize(msgObj.setHero);
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ProtoCSSetHeroReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}