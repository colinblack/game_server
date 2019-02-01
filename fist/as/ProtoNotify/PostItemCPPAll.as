package com.sanguo.game.server.connectlogic.common.message.ProtoNotify
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class PostItemCPPAll
	{
		public static const PROTO:String = "ProtoNotify.PostItemCPPAll";
		public var package_root:*;
		public  var message:*;
		public var invite:Vector.<MartialClubItemCpp>;
		public var battle:Vector.<MartialClubItemCpp>;
		public function PostItemCPPAll(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			invite = new Vector.<MartialClubItemCpp>();
			battle = new Vector.<MartialClubItemCpp>();
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.invite = [];
			for(var i:int = 0;i < this.invite.length;i++)
			{
				serializeObj.invite.push(this.invite[i].serialize());
			}
			serializeObj.battle = [];
			for(var i:int = 0;i < this.battle.length;i++)
			{
				serializeObj.battle.push(this.battle[i].serialize());
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):PostItemCPPAll
		{
			invite = new Vector.<MartialClubItemCpp>();
			battle = new Vector.<MartialClubItemCpp>();
			for(var i:int = 0;i < msgObj.invite.length;i++)
			{
				this.invite.push(new MartialClubItemCpp(package_root).unserialize(msgObj.invite[i]));
			}
			for(var i:int = 0;i < msgObj.battle.length;i++)
			{
				this.battle.push(new MartialClubItemCpp(package_root).unserialize(msgObj.battle[i]));
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):PostItemCPPAll
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}