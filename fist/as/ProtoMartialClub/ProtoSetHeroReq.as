package com.sanguo.game.server.connectlogic.common.message.ProtoMartialClub
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class ProtoSetHeroReq
	{
		public static const PROTO:String = "ProtoMartialClub.ProtoSetHeroReq";
		public var package_root:*;
		public  var message:*;
		public var detachUid:int;
		public var grade:int;
		public var heroId:int;
		public var slot:int;
		public function ProtoSetHeroReq(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			detachUid = undefined;
			grade = undefined;
			heroId = undefined;
			slot = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			if(this.detachUid!= undefined)
			{
				serializeObj.detachUid = this.detachUid;
			}
			if(this.grade!= undefined)
			{
				serializeObj.grade = this.grade;
			}
			serializeObj.heroId = this.heroId;
			serializeObj.slot = this.slot;
			return serializeObj;
		}
		public function unserialize(msgObj:*):ProtoSetHeroReq
		{
			detachUid = undefined;
			grade = undefined;
			heroId = undefined;
			slot = undefined;
			if(msgObj.hasOwnProperty("detachUid"))
			{
				this.detachUid = msgObj.detachUid;
			}
			if(msgObj.hasOwnProperty("grade"))
			{
				this.grade = msgObj.grade;
			}
			this.heroId = msgObj.heroId;
			this.slot = msgObj.slot;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ProtoSetHeroReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}