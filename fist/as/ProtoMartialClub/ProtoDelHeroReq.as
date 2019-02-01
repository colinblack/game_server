package com.sanguo.game.server.connectlogic.common.message.ProtoMartialClub
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class ProtoDelHeroReq
	{
		public static const PROTO:String = "ProtoMartialClub.ProtoDelHeroReq";
		public var package_root:*;
		public  var message:*;
		public var grade:int;
		public var heroId:int;
		public var slot:int;
		public function ProtoDelHeroReq(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			grade = undefined;
			heroId = undefined;
			slot = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.grade = this.grade;
			serializeObj.heroId = this.heroId;
			serializeObj.slot = this.slot;
			return serializeObj;
		}
		public function unserialize(msgObj:*):ProtoDelHeroReq
		{
			grade = undefined;
			heroId = undefined;
			slot = undefined;
			this.grade = msgObj.grade;
			this.heroId = msgObj.heroId;
			this.slot = msgObj.slot;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ProtoDelHeroReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}